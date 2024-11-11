#include "rasterizer.h"

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

void Rasterizer::output(char *outdir)
{
    for (int x = 0; x < width; x++)
    {
        for (int y = 0; y < height; y++)
        {
            std::cout << depth_buf[get_index(x, y)] << " ";
            Vector3f color = frame_buf[get_index(x, y)];
            image->set(x, y, TGAColor(color[0], color[1], color[2], 255));
        }
        std::cout << std::endl;
    }

    image->flip_vertically(); // i want to have the origin at the left bottom corner of the image
    image->write_tga_file(outdir);
}

void Rasterizer::draw_line(int x0, int y0, int x1, int y1, TGAColor color)
{
    bool steep = false;
    if (std::abs(x0 - x1) < std::abs(y0 - y1))
    {
        std::swap(x0, y0);
        std::swap(x1, y1);
        steep = true;
    }
    if (x0 > x1)
    {
        std::swap(x0, x1);
        std::swap(y0, y1);
    }
    int dx = x1 - x0;
    int dy = y1 - y0;
    int derror2 = std::abs(dy) * 2;
    int error2 = 0;
    int y = y0;
    for (int x = x0; x <= x1; x++)
    {
        if (steep)
        {
            image->set(y, x, color);
        }
        else
        {
            image->set(x, y, color);
        }
        error2 += derror2;
        if (error2 > dx)
        {
            y += (y1 > y0 ? 1 : -1);
            error2 -= dx * 2;
        }
    }
}

void Rasterizer::draw_triangle(Triangle Triangle)
{
    Triangle.getinfo();
    auto v = Triangle.toVector4();
    std::cout << Triangle.boxmax.x() << " " << Triangle.boxmax.y() << " " << Triangle.boxmax.z() << " " << Triangle.boxmin.x() << " " << Triangle.boxmin.y() << " " << Triangle.boxmin.z() << std::endl;
    for (int x = Triangle.boxmin.x(); x < Triangle.boxmax.x(); x++)
    {
        for (int y = Triangle.boxmin.y(); y < Triangle.boxmax.y(); y++)
        {

            if (isPointInTriangle({Triangle.v[0][0], Triangle.v[0][1]}, {Triangle.v[1][0], Triangle.v[1][1]}, {Triangle.v[2][0], Triangle.v[2][1]}, {x + 0.5, y + 0.5}))
            {
                std::tuple<float, float, float> barycentric_coords = computeBarycentric2D(x, y, Triangle.v);
                float alpha = std::get<0>(barycentric_coords);
                float beta = std::get<1>(barycentric_coords);
                float gamma = std::get<2>(barycentric_coords);
                float w_reciprocal = 1.0 / (alpha / v[0].w() + beta / v[1].w() + gamma / v[2].w());
                float z_interpolated = alpha * v[0].z() / v[0].w() + beta * v[1].z() / v[1].w() + gamma * v[2].z() / v[2].w();
                z_interpolated *= w_reciprocal;
                set_pixel({x, y, z_interpolated}, Triangle.color[0]);
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
