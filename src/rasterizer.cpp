
#include "rasterizer.h"
#include <random>
Rasterizer::Rasterizer(int w, int h) : width(w), height(h)
{
    image = new TGAImage(w, h, TGAImage::RGB);

    frame_buf.resize(w * h);
    depth_buf.resize(w * h);
    frame_buf.assign(frame_buf.size(), {255, 255, 255});
    depth_buf.assign(depth_buf.size(), 1000);
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

void Rasterizer::set_pixel(const Eigen::Vector3f &point, const Eigen::Vector3f &color)
{
    // old index: auto ind = point.y() + point.x() * width;
    auto ind = (height - 1 - point.y()) * width + point.x();

    if (point.z() < depth_buf[ind])
    {
        depth_buf[ind] = point.z();
        frame_buf[ind] = color;
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

void Rasterizer::output(char *outdir)
{
    for (int x = 0; x < width; x++)
    {
        for (int y = 0; y < height; y++)
        {

            Vector3f color = frame_buf[get_index(x, y)];
            image->set(x, y, TGAColor(color[0], color[1], color[2], 255));
        }
    }
    Rasterizer::show_window(*image);
    image->flip_vertically(); // i want to have the origin at the left bottom corner of the image
    image->write_tga_file(outdir);
}

// 绘制三角形函数，负责将给定的三角形光栅化到图像上
void Rasterizer::draw_triangle(Triangle Triangle, std::vector<Vector3f> view_pos, Texture *texture)
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

                // 插值计算颜色、法线、纹理坐标和视点位置
                auto interpolated_color = interpolate(alpha, beta, gamma, Triangle.color[0], Triangle.color[1], Triangle.color[2], 1);
                auto interpolated_normal = interpolate(alpha, beta, gamma, Triangle.normal[0], Triangle.normal[1], Triangle.normal[2], 1);
                auto interpolated_texcoords = interpolate(alpha, beta, gamma, Triangle.tex_coords[0], Triangle.tex_coords[1], Triangle.tex_coords[2], 1);
                auto interpolated_viewpos = interpolate(alpha, beta, gamma, view_pos[0], view_pos[1], view_pos[2], 1);

                // 准备片段着色器的输入数据
                fragment_shader_payload payload(interpolated_color / 255.0f, interpolated_normal.normalized(), interpolated_texcoords, texture, lights);
                payload.view_pos = interpolated_viewpos;
                // 调用片段着色器计算最终像素颜色
                auto pixel_color = fragment_shader(payload);

                // 设置像素的深度值和颜色
                set_pixel({x, y, z_interpolated}, pixel_color);
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
        std::cout << size << std::endl;
        for (int t = 0; t < size; t++)
        {
            Triangle *ori_t = models[i].get_triangles()[t];
            Triangle new_t;
            std::vector<Eigen::Vector3f> viewspace_pos;

            for (int n = 0; n < 3; n++)
            {
                viewspace_pos.push_back(get_view_pos(ori_t->v[n]));
            }

            for (int n = 0; n < 3; n++)
            {
                Vector3f new_vertex = Transform(ori_t->v[n], transform, 1.0f);
                new_vertex = World2Screen(new_vertex);
                new_t.setVertex(n, new_vertex);
            }

            for (int n = 0; n < 3; n++)
            {
                Vector3f new_normal = Transform(ori_t->normal[n], inv_trans, 0);
                new_t.setNormal(n, new_normal);
            }

            for (int n = 0; n < 3; n++)
            {
                new_t.setTexCoord(n, ori_t->tex_coords[n][0], ori_t->tex_coords[n][1]);
                new_t.setColor(n, ori_t->color[n][0], ori_t->color[n][1], ori_t->color[n][2]);
            }

            draw_triangle(new_t, viewspace_pos, models[i].get_Texture());
        }

        std::cout << "Model:" << models[i].name << "Have been render well" << std::endl;
    }
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

    std::fill(depth_buf.begin(), depth_buf.end(), std::numeric_limits<float>::infinity());
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

void Rasterizer::show_window(TGAImage &image)
{
    SDL_Surface *hello = nullptr;
    SDL_Window *window = nullptr;
    SDL_Surface *screenSurface = nullptr;

    // 初始化 SDL（SDL3 不再需要显式初始化每个子系统）
    SDL_Init(SDL_INIT_VIDEO);

    // 创建窗口（替换 SDL_SetVideoMode）
    window = SDL_CreateWindow("Window", 640, 480, SDL_WINDOW_HIDDEN);
    screenSurface = SDL_GetWindowSurface(window);

    // 显示窗口（SDL3 新增显式窗口显示）
    SDL_ShowWindow(window);

    // 图像渲染（保持相同但建议改用 SDL_Renderer）
    SDL_BlitSurface(hello, nullptr, screenSurface, nullptr);

    // 更新窗口（改用新 API）
    SDL_UpdateWindowSurface(window);

    // 延迟（保持相同）
    SDL_Delay(2000);

    // 释放资源（注意新增窗口销毁）
    SDL_DestroySurface(hello);
    SDL_DestroyWindow(window);
    SDL_Quit();
}