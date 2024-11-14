#include <Eigen/Core>
#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include "Triangle.hpp"
#include "Utils/tgaimage.h"
#include <Eigen/Dense>
#include "Shader/Shader.h"

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
    std::map<int, std::vector<Eigen::Vector3f>> nor_buf;
    std::map<int, std::vector<Eigen::Vector2f>> tex_buf;

    std::vector<Eigen::Vector3f> frame_buf;
    Texture texture;
    std::function<Eigen::Vector3f(fragment_shader_payload)> fragment_shader;
    std::function<Eigen::Vector3f(vertex_shader_payload)> vertex_shader;

    std::vector<float> depth_buf;

public:
    Rasterizer(int w, int h);
    ~Rasterizer();

    void Handle();

    void set_model(const Eigen::Matrix4f &m);

    void set_view(const Eigen::Matrix4f &v);

    void set_projection(const Eigen::Matrix4f &p);

    void add_pos_buf(int i, std::vector<Eigen::Vector3f> position);
    void add_ind_buf(int i, std::vector<Eigen::Vector3i> index);
    void add_col_buf(int i, std::vector<Eigen::Vector3f> color);
    void add_nor_buf(int i, std::vector<Eigen::Vector3f> normal);
    void add_tex_buf(int i, std::vector<Eigen::Vector2f> tex_crood);
    void set_vertex_shader(std::function<Eigen::Vector3f(vertex_shader_payload)> vert_shader);
    void set_fragment_shader(std::function<Eigen::Vector3f(fragment_shader_payload)> frag_shader);
    // void Rasterizer::clear(Buffers buff);

    int get_index(int x, int y);

    void set_pixel(const Eigen::Vector3f &point, const Eigen::Vector3f &color);
    void clear();
    void output(char *outdir);
    Vector3f get_view_pos(Vector3f v);
    void draw_line(int x0, int y0, int x1, int y1, TGAColor color);

    void draw_triangle(Triangle triangle, std::vector<Vector3f>);
    float crossProduct(Vector2f A, Vector2f B, Vector2f P);
    bool isPointInTriangle(Vector2f A, Vector2f B, Vector2f C, Vector2f P);
    std::tuple<float, float, float> computeBarycentric2D(float x, float y, const Vector3f *v);

    Vector3f Transform(Vector3f, Matrix4f, float);

    Vector3f World2Screen(Vector3f worldpos);
};
