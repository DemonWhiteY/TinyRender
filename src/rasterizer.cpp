
#include "rasterizer.h"
#include <random>
#include <thread>
// #include <omp.h>
#include "mingw.thread.h"
Rasterizer::Rasterizer(int w, int h) : width(w), height(h)
{

    frame_buf.resize(w * h);
    depth_buf.resize(w * h);
    model_buf.resize(w * h);
    frame_buf.assign(frame_buf.size(), {255, 255, 255});
    depth_buf.assign(depth_buf.size(), 1000);
    model_buf.assign(model_buf.size(), -1);
    shadow_depth_buf.resize(w * h);
    shadow_depth_buf.assign(shadow_depth_buf.size(), 1000);
}

Rasterizer::Rasterizer()
{
}

Rasterizer::~Rasterizer()
{
}

void Rasterizer::set_model(const Eigen::Matrix4f &m)
{
    model = m;
}

void Rasterizer::set_view(const Eigen::Matrix4f &v)
{
    view = v;
}

void Rasterizer::set_projection(const Eigen::Matrix4f &p)
{
    projection = p;
}

int Rasterizer::get_index(int x, int y)
{
    return (height - 1 - y) * width + x;
}

void Rasterizer::set_pixel(const Eigen::Vector3f &point, const Eigen::Vector3f &color, int modelnum)
{
    // old index: auto ind = point.y() + point.x() * width;
    auto ind = (height - 1 - point.y()) * width + point.x();

    if (point.z() < depth_buf[ind])
    {
        depth_buf[ind] = point.z();
        frame_buf[ind] = color;
        model_buf[ind] = modelnum;
    }
}

static Eigen::Vector3f interpolate(float alpha, float beta, float gamma, const Eigen::Vector3f &vert1, const Eigen::Vector3f &vert2, const Eigen::Vector3f &vert3, float weight)
{
    return (alpha * vert1 + beta * vert2 + gamma * vert3) / weight;
}

static Eigen::Vector2f interpolate(float alpha, float beta, float gamma, const Eigen::Vector2f &vert1, const Eigen::Vector2f &vert2, const Eigen::Vector2f &vert3, float weight)
{
    auto u = (alpha * vert1[0] + beta * vert2[0] + gamma * vert3[0]);
    auto v = (alpha * vert1[1] + beta * vert2[1] + gamma * vert3[1]);

    u /= weight;
    v /= weight;

    return Eigen::Vector2f(u, v);
}

void Rasterizer::output()
{
    std::vector<unsigned char> data(width * height * 3);
    for (int y = 0; y < height; ++y)
    {
        for (int x = 0; x < width; ++x)
        {
            int index = get_index(x, y);
            data[(y * width + x) * 3 + 0] = static_cast<unsigned char>(frame_buf[index].x());
            data[(y * width + x) * 3 + 1] = static_cast<unsigned char>(frame_buf[index].y());
            data[(y * width + x) * 3 + 2] = static_cast<unsigned char>(frame_buf[index].z());
        }
    }

    stbi_write_bmp("../output/output.bmp", width, height, 3, data.data());
}
bool Rasterizer::is_within_bounds(int x, int y, int z)
{
    // 假设 framebuffer 的尺寸为 width x height x depth
    return x >= 0 && x < width && y >= 0 && y < height;
}
void Rasterizer::draw_line(Vector3f v1, Vector3f v2, Vector3f color)
{
    int x0 = static_cast<int>(v1.x());
    int y0 = static_cast<int>(v1.y());
    int x1 = static_cast<int>(v2.x());
    int y1 = static_cast<int>(v2.y());
    int z0 = static_cast<int>(v1.z());
    int z1 = static_cast<int>(v2.z());
    int border_x0 = std::min(x0, x1);
    int border_x1 = std::max(x0, x1);
    int dx = abs(x1 - x0);
    int dy = abs(y1 - y0);
    int sx = (x0 < x1) ? 1 : -1;
    int sy = (y0 < y1) ? 1 : -1;
    int err = dx - dy;
    int dz = abs(v1.z() - v2.z());
    int x = x0;
    int y = y0;
    int z = z0;
    for (int i = 0; i <= dx + dy; ++i)
    {
        if (x > 0 && x < width && y > 0 && y < height && x >= border_x0 && x <= border_x1)
            set_pixel({x, y, z}, color, 0); // z坐标设置为0，可以根据需要调整
        int e2 = 2 * err;
        if (e2 > -dy)
        {
            err -= dy;
            x += sx;
            z += dz / dx * sx;
        }
        if (e2 < dx)
        {
            err += dx;
            y += sy;
            z += dz / dy * sy;
        }
    }
}
// 绘制三角形函数，负责将给定的三角形光栅化到图像上
void Rasterizer::draw_triangle(Triangle Triangle, std::vector<Vector3f> view_pos, std::vector<Vector3f> ori_pos, Texture *texture, int modelnum, bool shadow)
{
    // 获取三角形的顶点信息和其他相关数据
    Triangle.getinfo();

    // 将三角形的顶点转换为齐次坐标表示
    auto v = Triangle.toVector4();

    // 遍历三角形的包围盒内的每一个像素
    for (int x = std::max(Triangle.boxmin.x(), 0.0f); x < Triangle.boxmax.x() && x < width; x++)
    {
        for (int y = std::max(Triangle.boxmin.y(), 0.0f); y < Triangle.boxmax.y() && y < height; y++)
        {
            // 检查当前像素是否在三角形内部
            if (isPointInTriangle({Triangle.v[0][0], Triangle.v[0][1]}, {Triangle.v[1][0], Triangle.v[1][1]}, {Triangle.v[2][0], Triangle.v[2][1]}, {x + 0.5, y + 0.5}))
            {
                // 计算当前像素的重心坐标
                std::tuple<float, float, float> barycentric_coords = computeBarycentric2D(x, y, Triangle.v);
                float alpha = std::get<0>(barycentric_coords);
                float beta = std::get<1>(barycentric_coords);
                float gamma = std::get<2>(barycentric_coords);

                // 计算深度值的 reciprocate
                float w_reciprocal = 1.0 / (alpha / v[0].w() + beta / v[1].w() + gamma / v[2].w());
                // 使用重心坐标插值计算深度值
                float z_interpolated = alpha * v[0].z() / v[0].w() + beta * v[1].z() / v[1].w() + gamma * v[2].z() / v[2].w();
                z_interpolated *= w_reciprocal;

                // int index = get_index(x, y, width, height);
                // if (z_interpolated < shadow_depth_buf[index])
                // {
                //     shadow_depth_buf[index] = z_interpolated;
                // }

                // 插值计算颜色、法线、纹理坐标和视点位置
                auto interpolated_color = interpolate(alpha, beta, gamma, Triangle.color[0], Triangle.color[1], Triangle.color[2], 1);
                auto interpolated_normal = interpolate(alpha, beta, gamma, Triangle.normal[0], Triangle.normal[1], Triangle.normal[2], 1);
                auto interpolated_texcoords = interpolate(alpha, beta, gamma, Triangle.tex_coords[0], Triangle.tex_coords[1], Triangle.tex_coords[2], 1);
                auto interpolated_viewpos = interpolate(alpha, beta, gamma, view_pos[0], view_pos[1], view_pos[2], 1);
                auto interpolated_ori_pos = interpolate(alpha, beta, gamma, ori_pos[0], ori_pos[1], ori_pos[2], 1);
                // 准备片段着色器的输入数据
                fragment_shader_payload payload(interpolated_color / 255.0f, interpolated_normal.normalized(), interpolated_texcoords, texture, lights);
                payload.view_pos = interpolated_viewpos;
                payload.ori_pos = interpolated_ori_pos;
                payload.shadow_depth_buf = &shadow_depth_buf;
                // 调用片段着色器计算最终像素颜色
                auto pixel_color = fragment_shader(payload);
                if (shadow)
                {
                    auto light_view_martix = lights[0].light_camera->get_view_matrix();
                    auto light_projection_martix = lights[0].light_camera->get_projection_matrix();
                    Eigen::Matrix4f transform = light_projection_martix * light_view_martix;
                    auto result_pos = Transform(interpolated_ori_pos, transform, 1);
                    result_pos = World2Screen(result_pos);
                    if (result_pos[0] < width && result_pos[0] >= 0 && result_pos[1] < height && result_pos[1] >= 0)
                    {
                        auto z = shadow_depth_buf[get_index(result_pos[0], result_pos[1], width, height)];
                        if (result_pos[2] - z > 0.1)
                        {
                            pixel_color = Vector3f(20, 20, 20);
                        }
                    }
                }

                // 设置像素的深度值和颜色
                set_pixel({x, y, z_interpolated}, pixel_color, modelnum);
            }
        }
    }
}

float Rasterizer::crossProduct(Vector2f A, Vector2f B, Vector2f P)
{
    return (B[0] - A[0]) * (P[1] - A[1]) - (B[1] - A[1]) * (P[0] - A[0]);
}

bool Rasterizer::isPointInTriangle(Vector2f A, Vector2f B, Vector2f C, Vector2f P)
{
    float cross1 = crossProduct(A, B, P);
    float cross2 = crossProduct(B, C, P);
    float cross3 = crossProduct(C, A, P);

    // 检查叉积符号
    return (cross1 >= 0 && cross2 >= 0 && cross3 >= 0) || (cross1 <= 0 && cross2 <= 0 && cross3 <= 0);
}

std::tuple<float, float, float> Rasterizer::computeBarycentric2D(float x, float y, const Vector3f *v)
{
    float c1 = (x * (v[1].y() - v[2].y()) + (v[2].x() - v[1].x()) * y + v[1].x() * v[2].y() - v[2].x() * v[1].y()) / (v[0].x() * (v[1].y() - v[2].y()) + (v[2].x() - v[1].x()) * v[0].y() + v[1].x() * v[2].y() - v[2].x() * v[1].y());
    float c2 = (x * (v[2].y() - v[0].y()) + (v[0].x() - v[2].x()) * y + v[2].x() * v[0].y() - v[0].x() * v[2].y()) / (v[1].x() * (v[2].y() - v[0].y()) + (v[0].x() - v[2].x()) * v[1].y() + v[2].x() * v[0].y() - v[0].x() * v[2].y());
    float c3 = (x * (v[0].y() - v[1].y()) + (v[1].x() - v[0].x()) * y + v[0].x() * v[1].y() - v[1].x() * v[0].y()) / (v[2].x() * (v[0].y() - v[1].y()) + (v[1].x() - v[0].x()) * v[2].y() + v[0].x() * v[1].y() - v[1].x() * v[0].y());
    return {c1, c2, c3};
}

auto to_vec4(const Eigen::Vector3f &v3, float w = 1.0f)
{
    return Vector4f(v3.x(), v3.y(), v3.z(), w);
}

void Rasterizer::Handle()
{
    this->set_view(camera.get_view_matrix());
    this->set_projection(camera.get_projection_matrix());

    for (int i = 0; i < models.size(); i++)
    {
        this->set_model(models[i].get_model_matrix());

        Matrix4f transform = projection * view * model;
        Eigen::Matrix4f inv_trans = (view * model).inverse().transpose();
        int size = models[i].get_triangles().size();
        for (auto &light : lights)
        {
            light.final_position = Transform(light.position, view, 0);
        }
        render_to_shadow_map();
        if (model_select == i)
        {
            std::vector<Vector3f> new_vertices;
            new_vertices.resize(8);
            for (int j = 0; j < 8; j++)
            {
                new_vertices[j] = World2Screen(Transform(models[i].vertices[j], transform, 1.0f));
            }
            Eigen::Vector3f line_color(255, 0, 0); // 黑色

            // 绘制底部边
            draw_line(new_vertices[0], new_vertices[1], line_color);
            draw_line(new_vertices[1], new_vertices[7], line_color);
            draw_line(new_vertices[2], new_vertices[0], line_color);
            draw_line(new_vertices[7], new_vertices[2], line_color);

            // // 绘制顶部边
            draw_line(new_vertices[4], new_vertices[5], line_color);
            draw_line(new_vertices[5], new_vertices[3], line_color);
            draw_line(new_vertices[4], new_vertices[6], line_color);

            draw_line(new_vertices[6], new_vertices[3], line_color);

            // // 绘制连接边
            draw_line(new_vertices[0], new_vertices[3], line_color);
            draw_line(new_vertices[1], new_vertices[6], line_color);
            draw_line(new_vertices[2], new_vertices[5], line_color);
            draw_line(new_vertices[4], new_vertices[7], line_color);
        }

        for (int t = 0; t < size; t++)
        {
            Triangle *ori_t = models[i].get_triangles()[t];
            Triangle new_t;
            std::vector<Eigen::Vector3f> viewspace_pos;
            std::vector<Eigen::Vector3f> ori_pos;
            for (int n = 0; n < 3; n++)
            {
                ori_pos.push_back(get_ori_pos(ori_t->v[n]));
            }
            // 计算顶点位置并放入 viewspace_pos
            for (int n = 0; n < 3; n++)
            {
                viewspace_pos.push_back(get_view_pos(ori_t->v[n]));
            }

            // 变换顶点并设置新三角形的顶点
            for (int n = 0; n < 3; n++)
            {
                Vector3f new_vertex = Transform(ori_t->v[n], transform, 1.0f);
                new_vertex = World2Screen(new_vertex);
                new_t.setVertex(n, new_vertex);
            }

            // 变换法线并设置新三角形的法线
            for (int n = 0; n < 3; n++)
            {
                Vector3f new_normal = Transform(ori_t->normal[n], inv_trans, 0);
                new_t.setNormal(n, new_normal);
            }

            // 设置纹理坐标和颜色
            for (int n = 0; n < 3; n++)
            {
                new_t.setTexCoord(n, ori_t->tex_coords[n][0], ori_t->tex_coords[n][1]);
                new_t.setColor(n, ori_t->color[n][0], ori_t->color[n][1], ori_t->color[n][2]);
            }

            // 绘制三角形
            if (models[i].shadow_face)
            {
                draw_triangle(new_t, viewspace_pos, ori_pos, models[i].get_Texture(), i, true);
            }
            else
                draw_triangle(new_t, viewspace_pos, ori_pos, models[i].get_Texture(), i, false);
        }
    }

    output_shadow_map("../output/shadow_map.bmp", lights[0]);
}
Vector3f Rasterizer::get_ori_pos(Vector3f v)
{
    Vector4f newpos = {v.x(), v.y(), v.z(), 1.0};
    Vector4f result;
    result = model * newpos;
    return {result.x(), result.y(), result.z()};
}

Vector3f Rasterizer::get_view_pos(Vector3f v)
{
    Vector4f newpos = {v.x(), v.y(), v.z(), 1.0};
    Vector4f result;
    result = view * model * newpos;
    return {result.x(), result.y(), result.z()};
}

Vector3f Rasterizer::Transform(Vector3f position, Matrix4f transform, float f)
{
    Vector4f newpos = {position.x(), position.y(), position.z(), f};
    Vector4f result;
    result = transform * newpos;
    if (f == 0)

        return {result.x(), result.y(), result.z()};

    else
    {
        Vector3f NormalResult = {result[0] / result[3], result[1] / result[3], result[2] / result[3]};
        return {NormalResult.x(), NormalResult.y(), NormalResult.z()};
    }
}

Vector3f Rasterizer::World2Screen(Vector3f worldpos)
{
    Vector3f ScreenPos;
    ScreenPos.x() = (width + int(worldpos.x() * width)) / 2;
    ScreenPos.y() = (height + int(worldpos.y() * height)) / 2;
    ScreenPos.z() = -worldpos.z() * 100;
    return ScreenPos;
}

void Rasterizer::clear()
{

    std::fill(frame_buf.begin(), frame_buf.end(), Eigen::Vector3f{255, 255, 255});
    std::fill(shadow_depth_buf.begin(), shadow_depth_buf.end(), 1000);
    std::fill(depth_buf.begin(), depth_buf.end(), std::numeric_limits<float>::infinity());
    std::fill(model_buf.begin(), model_buf.end(), -1);
}

void Rasterizer::set_vertex_shader(std::function<Eigen::Vector3f(vertex_shader_payload)> vert_shader)
{
    vertex_shader = vert_shader;
}

void Rasterizer::set_fragment_shader(std::function<Eigen::Vector3f(fragment_shader_payload)> frag_shader)
{
    fragment_shader = frag_shader;
}

void Rasterizer::add_model(Model model)
{
    this->models.push_back(model);
}

void Rasterizer::write_scene_to_json(std::string &path)
{
    nlohmann::json root;

    // 写入模型信息
    nlohmann::json objects_json = nlohmann::json::array();
    for (const auto &model : this->models)
    {
        nlohmann::json model_json;
        model_json["name"] = model.name;
        model_json["objfile"] = model.filename;

        // 写入纹理或颜色信息
        if (model.texture)
        {
            model_json["texture"] = model.texture->get_file();
        }
        else
        {
            model_json["color"] = {model.color[0], model.color[1], model.color[2]};
        }

        // 写入变换属性
        model_json["scale"] = {model.scale[0], model.scale[1], model.scale[2]};
        model_json["rotation"] = {model.rotation[0], model.rotation[1], model.rotation[2]};
        model_json["translate"] = {model.translate[0], model.translate[1], model.translate[2]};

        objects_json.push_back(model_json);
    }
    root["objects"] = objects_json;

    // 写入灯光信息
    nlohmann::json lights_json = nlohmann::json::array();
    for (const auto &l : lights)
    {
        nlohmann::json light_json;
        light_json["name"] = l.name;
        light_json["position"] = {l.position[0], l.position[1], l.position[2]};
        light_json["intensity"] = {l.intensity[0], l.intensity[1], l.intensity[2]};
        lights_json.push_back(light_json);
    }
    root["lights"] = lights_json;

    // 写入相机信息
    nlohmann::json camera_json;
    camera_json["position"] = {camera.get_position()[0], camera.get_position()[1], camera.get_position()[2]};
    camera_json["target"] = {camera.get_target()[0], camera.get_target()[1], camera.get_target()[2]};
    camera_json["up"] = {camera.get_up()[0], camera.get_up()[1], camera.get_up()[2]};
    camera_json["fov"] = camera.get_eye_fov();
    camera_json["aspect"] = camera.get_aspect_ratio();
    camera_json["near"] = camera.get_zNear();
    camera_json["far"] = camera.get_zFar();
    root["camera"] = camera_json;

    // 写入JSON文件
    std::ofstream out(path);
    if (!out.is_open())
    {
        printf("[error] Can't open the output file!\n");
        return;
    }
    out << std::setw(4) << root << std::endl; // 使用std::setw(4)来格式化输出，使其更易读
}

void Rasterizer::render_to_shadow_map()
{

    for (auto &light : lights)
    {

        auto light_projection_matrix = light.light_camera->get_projection_matrix();
        auto light_view_matrix = light.light_camera->get_view_matrix();
        // 清除阴影贴图的深度缓冲区
        std::fill(shadow_depth_buf.begin(), shadow_depth_buf.end(), 1000);

        // 遍历所有模型并渲染到阴影贴图
        for (int i = 0; i < models.size(); i++)
        {
            auto light_model_matrix = models[i].get_model_matrix();

            Matrix4f transform = light_projection_matrix * light_view_matrix * light_model_matrix;
            int size = models[i].get_triangles().size();

            for (int t = 0; t < size; t++)
            {
                Triangle *ori_t = models[i].get_triangles()[t];
                Triangle new_t;

                // 变换顶点并设置新三角形的顶点
                for (int n = 0; n < 3; n++)
                {

                    Vector3f new_vertex = Transform(ori_t->v[n], transform, 1.0f);
                    new_vertex = World2Screen(new_vertex);
                    new_t.setVertex(n, new_vertex);
                }

                draw_triangle_to_shadow_map(new_t, light);
            }
        }
    }
}

void Rasterizer::draw_triangle_to_shadow_map(Triangle Triangle, light &l)
{
    // 获取三角形的顶点信息
    // 获取三角形的顶点信息和其他相关数据
    Triangle.getinfo();

    // 将三角形的顶点转换为齐次坐标表示
    auto v = Triangle.toVector4();

    // 遍历三角形的包围盒内的每一个像素
    for (int x = std::max(Triangle.boxmin.x(), 0.0f); x < Triangle.boxmax.x() && x < width; x++)
    {
        for (int y = std::max(Triangle.boxmin.y(), 0.0f); y < Triangle.boxmax.y() && y < height; y++)
        {
            // 检查当前像素是否在三角形内部
            if (isPointInTriangle({Triangle.v[0][0], Triangle.v[0][1]}, {Triangle.v[1][0], Triangle.v[1][1]}, {Triangle.v[2][0], Triangle.v[2][1]}, {x + 0.5, y + 0.5}))
            {
                // 计算当前像素的重心坐标
                std::tuple<float, float, float> barycentric_coords = computeBarycentric2D(x, y, Triangle.v);
                float alpha = std::get<0>(barycentric_coords);
                float beta = std::get<1>(barycentric_coords);
                float gamma = std::get<2>(barycentric_coords);

                // 计算深度值的 reciprocate
                float w_reciprocal = 1.0 / (alpha / v[0].w() + beta / v[1].w() + gamma / v[2].w());
                // 使用重心坐标插值计算深度值
                float z_interpolated = alpha * v[0].z() / v[0].w() + beta * v[1].z() / v[1].w() + gamma * v[2].z() / v[2].w();
                z_interpolated *= w_reciprocal;

                int index = get_index(x, y, width, height);
                if (z_interpolated < shadow_depth_buf[index])
                {
                    shadow_depth_buf[index] = z_interpolated;
                }
            }
        }
    }
}

int Rasterizer::get_index(int x, int y, int w, int h)
{
    return (h - 1 - y) * w + x;
}

void Rasterizer::output_shadow_map(const std::string &filename, light &light)
{

    std::vector<unsigned char> data(width * height);

    // 找到深度缓冲区中的最大和最小深度值
    float min_depth = *std::min_element(shadow_depth_buf.begin(), shadow_depth_buf.end());
    float max_depth = *std::max_element(shadow_depth_buf.begin(), shadow_depth_buf.end());
    float m_depth = min_depth;
    for (int i = 0; i < width * height; i++)
    {
        if (shadow_depth_buf[i] != max_depth && shadow_depth_buf[i] > m_depth)
        {
            m_depth = shadow_depth_buf[i];
        }
    }
    for (int i = 0; i < width * height; i++)
    {
        if (shadow_depth_buf[i] == max_depth)
            shadow_depth_buf[i] == m_depth;
    }
    //  将深度值映射到 [0, 255] 范围内的灰度值
    for (int y = 0; y < height; ++y)
    {
        for (int x = 0; x < width; ++x)
        {
            int index = get_index(x, y, width, height);
            float depth = shadow_depth_buf[index];

            unsigned char gray = static_cast<unsigned char>((depth - min_depth) / (m_depth - min_depth) * 255.0f);

            data[y * width + x] = gray;
        }
    }

    // 保存灰度图像
    stbi_write_bmp(filename.c_str(), width, height, 1, data.data());
}
