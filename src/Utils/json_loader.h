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
        std::string texture = object["texture"];
        std::cout << "load:: " << name << "  path::" << objfile << std::endl;

        models.push_back(new Model(objfile, name));
        if (!texture.empty())
        {
            models.back()->set_Texture(new Texture(texture));
        }
        models.back()->set_Transform({1.0f, 1.0f, 1.0f}, {0, 140, 0}, {0, 0, 0});
    }
}

json_loader::~json_loader()
{
}
