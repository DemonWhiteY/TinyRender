#pragma once
#include <Eigen/Core>
#include <iostream>
#include "Camera.h"
class light
{
public:
    Eigen::Vector3f position;
    Eigen::Vector3f final_position;
    Eigen::Vector3f intensity;
    std::string name;
    std::vector<float> shadow_depth_buf;
    int depth_buf_size = 900;
    Camera *light_camera;
    light(Eigen::Vector3f position, Eigen::Vector3f intensity, std::string name) : position(position), intensity(intensity), name(name)
    {
    }
    ~light()
    {
        // delete light_camera;
    }
    void Init()
    {
        std::cout << "light init" << std::endl;
        light_camera = new Camera();
        light_camera->set_position(position, Eigen::Vector3f(0, 1, 0), Eigen::Vector3f(0, 0, 0));
    }
    std::vector<float> &get_shadow_depth_buf()
    {
        return shadow_depth_buf;
    }
    Eigen::Vector3f Transform(Eigen::Vector3f position, Eigen::Matrix4f transform, float f)
    {
        Eigen::Vector4f newpos = {position.x(), position.y(), position.z(), f};
        Eigen::Vector4f result;
        result = transform * newpos;
        result[0] = (900 + int(result[0]) * 900) / 2;
        result[1] = (900 + int(result[1]) * 900) / 2;
        result[2] = -result[2] * 100;
        return {result.x(), result.y(), result.z()};
    }

    Eigen::Vector3f World2Screen(Eigen::Vector3f worldpos)
    {
        Eigen::Vector3f ScreenPos;
        ScreenPos.x() = (depth_buf_size + int(worldpos.x() * depth_buf_size)) / 2;
        ScreenPos.y() = (depth_buf_size + int(worldpos.y() * depth_buf_size)) / 2;
        ScreenPos.z() = -worldpos.z() * 100;
        return ScreenPos;
    }
};
