#include "Camera.h"
constexpr double MY_PI = 3.1415926;

inline double DEG2RAD(double deg) { return deg * MY_PI / 180; }

Camera::Camera(/* args */)
{
    position = {0, 0, 5};
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

Eigen::Matrix4f Camera::get_view_matrix()
{
    Eigen::Matrix4f view = Eigen::Matrix4f::Identity();

    // 计算摄像机的三个坐标轴
    Eigen::Vector3f forward = (position - target).normalized(); // 计算前向
    Eigen::Vector3f right = up.cross(forward).normalized();     // 右向（上向与前向叉积）
    Eigen::Vector3f new_up = forward.cross(right).normalized(); // 重新计算上向

    // 旋转矩阵：将世界坐标系转换到摄像机坐标系
    Eigen::Matrix4f rotate;
    rotate << right[0], new_up[0], forward[0], 0,
        right[1], new_up[1], forward[1], 0,
        right[2], new_up[2], forward[2], 0,
        0, 0, 0, 1;

    // 计算平移矩阵
    Eigen::Matrix4f translate;
    translate << 1, 0, 0, -position[0],
        0, 1, 0, -position[1],
        0, 0, 1, -position[2],
        0, 0, 0, 1;

    // 视图矩阵 = 旋转矩阵 * 平移矩阵
    view = rotate * translate;

    return view;
}

Eigen::Matrix4f Camera::get_projection_matrix()
{
    // TODO: Copy-paste your implementation from the previous assignment.
    Eigen::Matrix4f projection;
    float top = -tan(DEG2RAD(eye_fov / 2.0f) * abs(zNear));
    float right = top * aspect_ratio;

    projection << zNear / right, 0, 0, 0,
        0, zNear / top, 0, 0,
        0, 0, (zNear + zFar) / (zNear - zFar), (2 * zNear * zFar) / (zFar - zNear),
        0, 0, 1, 0;
    return projection;
}
