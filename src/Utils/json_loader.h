#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <nlohmann/json.hpp> // 使用 nlohmann/json 库
#include "../Sence/Model.h"
#include "../Texture.h"

class json_loader
{
private:
    std::vector<Model *> models;

public:
    json_loader(std::string path);
    ~json_loader();
    std::vector<Model *> get_models()
    {
        return models;
    }
};

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

    for (const auto &object : root["objects"])
    {
        std::string name = object["name"];
        std::string objfile = object["objfile"];
        models.push_back(new Model(objfile, name));
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
}

json_loader::~json_loader()
{
}
