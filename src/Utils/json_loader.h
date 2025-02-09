#pragma once
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
json_loader::json_loader(std::string path)
{
    // 使用 nlohmann/json 进行解析
    std::ifstream in(path);
    if (!in.is_open())
    {
        printf("[error] Can't open the config file!\n");
    }

    nlohmann::json root;
    try
    {
        in >> root; // 直接解析 JSON 文件
    }
    catch (const std::exception &e)
    {
        std::cout << "[error] Failed to parse JSON: " << e.what() << std::endl;
        return;
    }

    // 遍历 JSON 对象，创建模型并设置属性
    for (const auto &object : root["objects"])
    {
        std::string name = object["name"];
        std::string objfile = object["objfile"];
        models.push_back(new Model(objfile, name));

        // 设置模型纹理或颜色
        if (object.contains("texture"))
        {
            std::cout << "texture" << std::endl;
            std::string texture = object.value("texture", "");
            if (!texture.empty())
            {
                models.back()->set_Texture(new Texture(texture));
            }
        }
        else if (object.contains("color"))
        {
            models.back()->color[0] = object["color"][0];
            models.back()->color[1] = object["color"][1];
            models.back()->color[2] = object["color"][2];
            models.back()->set_color();
        }
        else
        {
            models.back()->color[0] = 20;
            models.back()->color[1] = 220;
            models.back()->color[2] = 20;
            models.back()->set_color();
        }

        // 设置模型变换属性：缩放、旋转和平移
        models.back()->scale[0] = object["scale"][0];
        models.back()->scale[1] = object["scale"][1];
        models.back()->scale[2] = object["scale"][2];

        models.back()->rotation[0] = object["rotation"][0];
        models.back()->rotation[1] = object["rotation"][1];
        models.back()->rotation[2] = object["rotation"][2];

        models.back()->translate[0] = object["translate"][0];
        models.back()->translate[1] = object["translate"][1];
        models.back()->translate[2] = object["translate"][2];

        models.back()->set_Transform(models.back()->scale, models.back()->rotation, models.back()->translate);
    }

    // 遍历 JSON 灯光，创建灯光并设置属性
    for (const auto &_light : root["lights"])
    {
        auto l = light{{0, 0, 0}, {0, 0, 0}};
        l.position[0] = _light["position"][0];
        l.position[1] = _light["position"][1];
        l.position[2] = _light["position"][2];
        l.intensity[0] = _light["intensity"][0];
        l.intensity[1] = _light["intensity"][1];
        l.intensity[2] = _light["intensity"][2];

        lights.push_back(l);
    }

    Vector3f position, target, up;
    for (int i = 0; i < 3; i++)
    {
        position[i] = root["camera"]["position"][i];
        target[i] = root["camera"]["target"][i];
        up[i] = root["camera"]["up"][i];
    }

    camera.set_position(position, up, target);
    camera.set_ratio(root["camera"]["fov"], root["camera"]["aspect"], root["camera"]["near"], root["camera"]["far"]);
}

json_loader::~json_loader()
{
}
