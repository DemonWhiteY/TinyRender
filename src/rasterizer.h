#include <Eigen/Core>
#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include "Triangle.hpp"
#include "tgaimage.h"
using namespace Eigen;

enum class Buffers
{
    Color = 1,
    Depth = 2
};

struct ScreenPoint
{
    float x, y;
};

class Rasterizer
{
private:
    TGAImage *image;
    int width, height;
    Eigen::Matrix4f model;
    Eigen::Matrix4f view;
    Eigen::Matrix4f projection;

    std::map<int, std::vector<Eigen::Vector3f>> pos_buf;
    std::map<int, std::vector<Eigen::Vector3i>> ind_buf;
    std::map<int, std::vector<Eigen::Vector3f>> col_buf;

    std::vector<Eigen::Vector3f> frame_buf;

    std::vector<float> depth_buf;

public:
    Rasterizer(int w, int h);
    ~Rasterizer();

    void set_model(const Eigen::Matrix4f &m);

    void set_view(const Eigen::Matrix4f &v);

    void set_projection(const Eigen::Matrix4f &p);

    // void Rasterizer::clear(Buffers buff);

    int get_index(int x, int y);

    void set_pixel(const Eigen::Vector3f &point, const Eigen::Vector3f &color);

    void output(char *outdir);

    void draw_line(int x0, int y0, int x1, int y1, TGAColor color);

    void draw_triangle(Triangle triangle);
    float crossProduct(Vector2f A, Vector2f B, Vector2f P);
    bool isPointInTriangle(Vector2f A, Vector2f B, Vector2f C, Vector2f P);
    std::tuple<float, float, float> computeBarycentric2D(float x, float y, const Vector3f *v);
};
