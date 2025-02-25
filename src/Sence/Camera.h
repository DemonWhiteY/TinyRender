#pragma once
#include <Eigen/Core>
#include <Eigen/Dense>
class Camera
{
private:
    Eigen::Vector3f position, up, target;
    float eye_fov;
    float aspect_ratio;
    float zNear;
    float zFar;

public:
    Camera(/* args */);
    ~Camera();
    void set_position(Eigen::Vector3f position, Eigen::Vector3f up, Eigen::Vector3f target);
    void set_ratio(float eye_fov, float aspect_ratio, float zNear, float zFar);
    Eigen::Vector3f get_position() { return position; }
    Eigen::Vector3f get_up() { return up; }
    Eigen::Vector3f get_target() { return target; }
    float get_eye_fov() { return eye_fov; }
    float get_aspect_ratio() { return aspect_ratio; }
    float get_zNear() { return zNear; }
    float get_zFar() { return zFar; }
    Eigen::Matrix4f get_view_matrix();
    Eigen::Matrix4f get_projection_matrix();
};
