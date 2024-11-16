#ifndef MODEL_H
#define MODEL_H

#include "../Triangle.hpp"
#include "../Texture.h"
#include "../Utils/objects_loader.h"
#include <iostream>
#include <vector>
#include <memory>
class Model
{
private:
    std::string filename = "";
#include <memory> // 引入智能指针库

    std::vector<Triangle *> triangles; // 使用 unique_ptr 管理内存

    Vector3f scale;
    Vector3f rotation;
    Vector3f translate;
    Texture *texture;

public:
    std::string name;

    Model(/* args */);
    Model(const std::string &filename, const std::string &name);
    ~Model();
    void load_triangles(std::vector<Vector3f>, std::vector<Vector3f>, std::vector<Vector3f>, std::vector<Vector3i>, std::vector<Vector2f>);
    std::vector<Triangle *> get_triangles() { return triangles; }
    void set_Texture(Texture *t) { texture = t; };
    Texture *get_Texture() { return texture; }
    Eigen::Matrix4f get_model_matrix();
    void set_Transform(Vector3f s, Vector3f r, Vector3f t)
    {
        scale = s;
        rotation = r, translate = t;
    }
};

#endif