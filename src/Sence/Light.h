#pragma once
#include <Eigen/Core>
#include <iostream>
class light
{
public:
    Eigen::Vector3f position;
    Eigen::Vector3f intensity;
    std::string name;
};
