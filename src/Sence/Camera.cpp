#include "Camera.h"

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
