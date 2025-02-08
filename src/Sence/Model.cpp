#include "Model.h"
constexpr double MY_PI = 3.1415926;

inline double DEG2RAD(double deg) { return deg * MY_PI / 180; }
Model::Model(const std::string &filename, const std::string &name)
{
    this->name = name;
    std::vector<Vector3f> position, normal;
    std::vector<Vector3i> index;
    std::vector<Vector2f> texCroods;
    objects_loader loader;
    loader.load_obj(filename, position, index, normal, texCroods);
    std::cout << "load_model" << std::endl;
    this->load_triangles(position, normal, index, texCroods);
}

Model::Model(/* args */)
{
}

Model::~Model()
{
}

void Model::load_triangles(std::vector<Vector3f> position, std::vector<Vector3f> normal, std::vector<Vector3i> index, std::vector<Vector2f> texCrood)
{
    for (int i = 0; i < index.size(); i++)
    {

        auto temp_triangle = new Triangle();
        for (int m = 0; m < 3; m++)
        {

            temp_triangle->setVertex(m, position[i * 3 + m]);
            temp_triangle->setNormal(m, normal[i * 3 + m]);
            if (texCrood.size() != 0)
            {
                temp_triangle->setTexCoord(m, texCrood[i * 3 + m][0], texCrood[i * 3 + m][1]);
            }
        }

        this->triangles.push_back(temp_triangle);
    }
}

Eigen::Matrix4f Model::get_model_matrix()
{
    // 创建单位矩阵
    Eigen::Matrix4f model_matrix = Eigen::Matrix4f::Identity();

    // 缩放矩阵
    Eigen::Matrix4f scale_matrix = Eigen::Matrix4f::Identity();
    scale_matrix(0, 0) = scale.x();
    scale_matrix(1, 1) = scale.y();
    scale_matrix(2, 2) = scale.z();

    // 旋转矩阵 (绕 X, Y, Z 轴旋转)
    Eigen::Matrix4f rotation_matrix = Eigen::Matrix4f::Identity();

    // 旋转角度转换为弧度
    float rad_x = rotation.x() * MY_PI / 180.0f;
    float rad_y = rotation.y() * MY_PI / 180.0f;
    float rad_z = rotation.z() * MY_PI / 180.0f;

    // 绕 X 轴旋转矩阵
    Eigen::Matrix4f rot_x = Eigen::Matrix4f::Identity();
    rot_x(1, 1) = cos(rad_x);
    rot_x(1, 2) = -sin(rad_x);
    rot_x(2, 1) = sin(rad_x);
    rot_x(2, 2) = cos(rad_x);

    // 绕 Y 轴旋转矩阵
    Eigen::Matrix4f rot_y = Eigen::Matrix4f::Identity();
    rot_y(0, 0) = cos(rad_y);
    rot_y(0, 2) = sin(rad_y);
    rot_y(2, 0) = -sin(rad_y);
    rot_y(2, 2) = cos(rad_y);

    // 绕 Z 轴旋转矩阵
    Eigen::Matrix4f rot_z = Eigen::Matrix4f::Identity();
    rot_z(0, 0) = cos(rad_z);
    rot_z(0, 1) = -sin(rad_z);
    rot_z(1, 0) = sin(rad_z);
    rot_z(1, 1) = cos(rad_z);

    // 综合旋转矩阵（按 Z, Y, X 顺序）
    rotation_matrix = rot_z * rot_y * rot_x;

    // 平移矩阵
    Eigen::Matrix4f translate_matrix = Eigen::Matrix4f::Identity();
    translate_matrix(0, 3) = translate.x();
    translate_matrix(1, 3) = translate.y();
    translate_matrix(2, 3) = translate.z();

    // 最终的模型矩阵：先旋转，再缩放，最后平移
    model_matrix = translate_matrix * rotation_matrix * scale_matrix;

    return model_matrix;
}