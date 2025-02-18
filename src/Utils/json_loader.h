#ifndef JSON_LOADER_H
#define JSON_LOADER_H
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <nlohmann/json.hpp> // 使用 nlohmann/json 库
#include "../Sence/Model.h"
#include "../Sence/Light.h"
#include "../Sence/Camera.h"
#include "../Texture.h"

class json_loader
{
private:
    std::vector<Model *> models;
    std::vector<light> lights;
    Camera camera;

public:
    json_loader(std::string path);
    ~json_loader();
    std::vector<Model *> get_models()
    {
        return models;
    }

    std::vector<light> get_lights()
    {
        return lights;
    }

    Camera get_camera()
    {
        return camera;
    }
};

// JsonLoader 类的构造函数，用于加载 JSON 配置文件
// JsonLoader 类的构造函数，用于加载和解析 JSON 配置文件

#endif