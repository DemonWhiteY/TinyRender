//
// Created by LEI XU on 4/27/19.
//
#ifndef SHADER_H
#define SHADER_H

#include <Eigen/Eigen>
#include "../Texture.h"
#include "../Sence/light.h"

struct fragment_shader_payload
{
    fragment_shader_payload()
    {
        texture = nullptr;
    }

    fragment_shader_payload(const Eigen::Vector3f &col, const Eigen::Vector3f &nor, const Eigen::Vector2f &tc, Texture *tex, std::vector<light> l) : color(col), normal(nor), tex_coords(tc), texture(tex), lights(l) {}

    Eigen::Vector3f view_pos;
    Eigen::Vector3f ori_pos;
    Eigen::Vector3f color;
    Eigen::Vector3f normal;
    Eigen::Vector2f tex_coords;
    Texture *texture;
    std::vector<light> lights;
    std::vector<float> *shadow_depth_buf;
};

struct vertex_shader_payload
{
    Eigen::Vector3f position;
};

Eigen::Vector3f normal_fragment_shader(const fragment_shader_payload &payload);
Eigen::Vector3f phong_fragment_shader(const fragment_shader_payload &payload);
Eigen::Vector3f texture_fragment_shader(const fragment_shader_payload &payload);

#endif // RASTERIZER_SHADER_H