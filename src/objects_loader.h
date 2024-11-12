#ifndef OBJECTS_LOADER_H
#define OBJECTS_LOADER_H

#include "tiny_obj_loader.h"
#include <iostream>
#include <vector>
#include <Eigen/Core>
class objects_loader
{
private:
    /* data */
public:
    objects_loader(/* args */);
    ~objects_loader();
    void load_obj(const std::string &filename, std::vector<Eigen::Vector3f> &positions, std::vector<Eigen::Vector3i> &indices);
    void load_obj_withoutuv(const std::string &filename, std::vector<Eigen::Vector3f> &positions, std::vector<Eigen::Vector3i> &indices);
    void load_obj_without_normal(const std::string &filename, std::vector<Eigen::Vector3f> &positions, std::vector<Eigen::Vector3i> &indices);
};
#endif