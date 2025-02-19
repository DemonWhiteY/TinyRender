#ifndef MODEL_H
#define MODEL_H

#include "../Triangle.hpp"
#include "../Texture.h"
#include "../Utils/objects_loader.h"
#include <iostream>
#include <vector>
#include <memory>
// 引入智能指针库
class Model
{
private:
        std::vector<Triangle *> triangles; // 使用 unique_ptr 管理内存

public:
    std::string name;
    Vector3f scale;
    Vector3f rotation;
    Vector3f translate;
    Vector3f color;
    Texture *texture = nullptr;
    std::string filename = "";

    Model(/* args */);
    Model(const std::string &filename, const std::string &name);
    ~Model();
    void load_triangles(std::vector<Vector3f>, std::vector<Vector3f>, std::vector<Vector3i>, std::vector<Vector2f>);
    std::vector<Triangle *> get_triangles() { return triangles; }
    void set_Texture(Texture *t) { texture = t; };
    Texture *get_Texture() { return texture; }
    Eigen::Matrix4f get_model_matrix();
    void set_Transform(Vector3f s, Vector3f r, Vector3f t)
    {
        scale = s;
        rotation = r, translate = t;
    }

    void set_color()
    {
        for (auto &t : triangles)
        {
            t->setColor(0, color[0], color[1], color[2]);
            t->setColor(1, color[0], color[1], color[2]);
            t->setColor(2, color[0], color[1], color[2]);
        }
    }
};

#endif