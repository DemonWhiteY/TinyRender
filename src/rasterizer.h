#include <Eigen/Core>
#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include "Triangle.hpp"
#include "Utils/tgaimage.h"
#include <Eigen/Dense>
#include "Shader/Shader.h"
#include "Sence/Model.h"
#include "Sence/Camera.h"
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
    std::vector<Model> models;
    std::vector<light> lights;
    Camera camera;
    std::vector<Eigen::Vector3f> frame_buf;

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

    void add_model(Model);
    void add_light(light l) { this->lights.push_back(l); };
    void add_camera(Camera camera) { this->camera = camera; };
    void set_vertex_shader(std::function<Eigen::Vector3f(vertex_shader_payload)> vert_shader);
    void set_fragment_shader(std::function<Eigen::Vector3f(fragment_shader_payload)> frag_shader);
    // void Rasterizer::clear(Buffers buff);

    int get_index(int x, int y);

    void set_pixel(const Eigen::Vector3f &point, const Eigen::Vector3f &color);
    void clear();

    void draw_triangle(Triangle triangle, std::vector<Vector3f>, Texture *);
    void output(char *outdir);

    Vector3f get_view_pos(Vector3f v);
    float crossProduct(Vector2f A, Vector2f B, Vector2f P);
    bool isPointInTriangle(Vector2f A, Vector2f B, Vector2f C, Vector2f P);
    std::tuple<float, float, float> computeBarycentric2D(float x, float y, const Vector3f *v);
    Vector3f Transform(Vector3f, Matrix4f, float);
    Vector3f World2Screen(Vector3f worldpos);
};
