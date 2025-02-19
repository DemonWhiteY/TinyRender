#ifndef RASTERIZER_H
#define RASTERIZER_H
#include <Eigen/Core>
#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <thread>
#include <mutex>
#include "Triangle.hpp"
#include <Eigen/Dense>
#include "Shader/Shader.h"
#include "Sence/Model.h"
#include "Sence/Camera.h"
#include "SDL3/SDL.h"
#include "stb_image.h"
#include "stb_image_write.h"
#include <nlohmann/json.hpp> // 使用 nlohmann/json 库
#include <fstream>
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
    Eigen::Matrix4f model;
    Eigen::Matrix4f view;
    Eigen::Matrix4f projection;
    std::vector<Model> models;
    std::vector<light> lights;
    Camera camera;
    std::vector<float> depth_buf;
    std::vector<float> model_buf;
    std::vector<Eigen::Vector3f> frame_buf;

    std::function<Eigen::Vector3f(fragment_shader_payload)> fragment_shader;
    std::function<Eigen::Vector3f(vertex_shader_payload)> vertex_shader;

public:
    int width, height;
    Rasterizer();
    Rasterizer(int w, int h);
    ~Rasterizer();

    void Handle();

    std::vector<Model> &get_models()
    {
        return models;
    };

    std::vector<light> &get_lights()
    {
        return lights;
    }

    Camera &get_camera()
    {
        return camera;
    }
    void set_model(const Eigen::Matrix4f &m);

    void set_view(const Eigen::Matrix4f &v);

    void set_projection(const Eigen::Matrix4f &p);

    void add_model(Model);

    int get_pixel_model(int x, int y)
    {
        auto ind = (height - 1 - y) * width + x;
        return model_buf[ind];
    }
    void add_light(light l) { this->lights.push_back(l); };
    void add_camera(Camera camera) { this->camera = camera; };
    void set_vertex_shader(std::function<Eigen::Vector3f(vertex_shader_payload)> vert_shader);
    void set_fragment_shader(std::function<Eigen::Vector3f(fragment_shader_payload)> frag_shader);
    // void Rasterizer::clear(Buffers buff);

    int get_index(int x, int y);

    void set_pixel(const Eigen::Vector3f &point, const Eigen::Vector3f &color, int);
    void clear();

    void draw_triangle(Triangle triangle, std::vector<Vector3f>, Texture *, int);
    void output();

    Vector3f get_view_pos(Vector3f v);
    float crossProduct(Vector2f A, Vector2f B, Vector2f P);
    bool isPointInTriangle(Vector2f A, Vector2f B, Vector2f C, Vector2f P);
    std::tuple<float, float, float> computeBarycentric2D(float x, float y, const Vector3f *v);
    Vector3f Transform(Vector3f, Matrix4f, float);
    Vector3f World2Screen(Vector3f worldpos);
    void Edge_Detection();

    void clear_all()
    {
        models.clear();
        lights.clear();
        clear();
    }

    void write_scene_to_json(const std::string &path);
};

#endif
