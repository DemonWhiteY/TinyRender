//
// Created by LEI XU on 4/11/19.
//

#include "Triangle.hpp"
#include <algorithm>
#include <iostream>
#include <array>

Triangle::Triangle()
{
    v[0] << 0, 0, 0;
    v[1] << 0, 0, 0;
    v[2] << 0, 0, 0;

    color[0] << 0.0, 0.0, 0.0;
    color[1] << 0.0, 0.0, 0.0;
    color[2] << 0.0, 0.0, 0.0;

    tex_coords[0] << 0.0, 0.0;
    tex_coords[1] << 0.0, 0.0;
    tex_coords[2] << 0.0, 0.0;
}

void Triangle::setVertex(int ind, Vector3f ver)
{
    v[ind] = ver;
}
void Triangle::setNormal(int ind, Vector3f n)
{
    normal[ind] = n;
}
void Triangle::setColor(int ind, float r, float g, float b)
{
    if ((r < 0.0) || (r > 255.) ||
        (g < 0.0) || (g > 255.) ||
        (b < 0.0) || (b > 255.))
    {
        fprintf(stderr, "ERROR! Invalid color values");
        fflush(stderr);
        exit(-1);
    }

    color[ind] = Vector3f(r, g, b);
    return;
}
void Triangle::setTexCoord(int ind, float s, float t)
{
    tex_coords[ind] = Vector2f(s, t);
}

std::array<Vector4f, 3> Triangle::toVector4() const
{
    std::array<Eigen::Vector4f, 3> res;
    std::transform(std::begin(v), std::end(v), res.begin(), [](auto &vec)
                   { return Eigen::Vector4f(vec.x(), vec.y(), vec.z(), 1.f); });
    return res;
}

void Triangle::getinfo()
{
    boxmax = {std::max(v[0][0], std::max(v[1][0], v[2][0])), std::max(v[0][1], std::max(v[1][1], v[2][1]))};
    boxmin = {std::min(v[0][0], std::min(v[1][0], v[2][0])), std::min(v[0][1], std::min(v[1][1], v[2][1]))};
}
