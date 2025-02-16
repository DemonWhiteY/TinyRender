#ifndef MAIN_H
#define MAIN_H

#include "Utils/objects_loader.h"
#include <conio.h>
#include "Utils/json_loader.h"
#include "Utils/ui.h"
constexpr double MY_PI = 3.1415926;

inline double DEG2RAD(double deg) { return deg * MY_PI / 180; }

// 主函数，接收命令行参数
int main(int argc, char **argv)
{
    // 创建一个900x900的光栅化器对象
    Rasterizer *ras = new Rasterizer(900, 900);

    // 创建一个JSON加载器对象，用于解析指定的JSON文件
    json_loader json_loader("../test.JSON");

    // 从JSON文件中加载模型和光源信息
    std::vector<Model *> models = json_loader.get_models();
    std::vector<light> lights = json_loader.get_lights();

    // 遍历并添加所有加载的模型到光栅化器中
    for (auto model : models)
    {
        ras->add_model(*model);
    }

    // 遍历并添加所有加载的光源到光栅化器中
    for (auto light : lights)
    {
        ras->add_light(light);
    }

    // 添加相机信息到光栅化器中
    ras->add_camera(json_loader.get_camera());

    // 设置光栅化器的片段着色器为纹理片段着色器
    ras->set_fragment_shader(texture_fragment_shader);

    // 处理光栅化器的所有设置和添加的操作
    ras->Handle();

    // 将光栅化器的输出保存到指定的TGA文件中
    ras->output();
    gui *GUI = new gui(ras->width, ras->height);
    GUI->get_rasterizer(ras);
    GUI->windowsStart();

    return 0;
}

#endif
