#include "Camera.h"

Camera::Camera(/* args */)
{
    position = {5, 0, 0};
    up = {0, 1, 0};
    target = {0, 0, 0};
    eye_fov = 60;
    aspect_ratio = 16 / 9;
    zNear = 0.1;
    zFar = 10;
}

Camera::~Camera()
{
}

void Camera::set_position(Eigen::Vector3f position, Eigen::Vector3f up, Eigen::Vector3f target)
{
    this->position = position;
    this->up = up;
    this->target = target;
}
void Camera::set_ratio(float eye_fov, float aspect_ratio, float zNear, float zFar)
{
    this->eye_fov = eye_fov;
    this->aspect_ratio = aspect_ratio;
    this->zNear = zNear;
    this->zFar = zFar;
}
