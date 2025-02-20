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
    this->load_triangles(position, normal, index, texCroods);
    this->filename = filename;
    if (position.empty())
    {
        // 如果 position 为空，初始化 min_bounds 和 max_bounds 为零向量
        min_bounds = Vector3f(0, 0, 0);
        max_bounds = Vector3f(0, 0, 0);
    }
    else
    {
        min_bounds = Vector3f(0, 0, 0);
        max_bounds = Vector3f(0, 0, 0);

        // // 遍历 position 向量，更新 min_bounds 和 max_bounds
        for (const auto &pos : position)
        {
            min_bounds[0] = std::min(min_bounds.x(), pos.x());
            min_bounds[1] = std::min(min_bounds.y(), pos.y());
            min_bounds[2] = std::min(min_bounds.z(), pos.z());

            max_bounds[0] = std::max(max_bounds.x(), pos.x());
            max_bounds[1] = std::max(max_bounds.y(), pos.y());
            max_bounds[2] = std::max(max_bounds.z(), pos.z());
        }
        get_vertices();
    }

    // // 初始化 min_bounds 和 max_bounds 为第一个顶点的位置
}

Model::Model(/* args */)
{
}

Model::~Model()
{
}

void Model::get_vertices()
{
    vertices.resize(8);
    vertices[0] = min_bounds;
    vertices[1] = Vector3f(max_bounds.x(), min_bounds.y(), min_bounds.z());
    vertices[2] = Vector3f(min_bounds.x(), max_bounds.y(), min_bounds.z());
    vertices[3] = Vector3f(min_bounds.x(), min_bounds.y(), max_bounds.z());
    vertices[4] = max_bounds;
    vertices[5] = Vector3f(min_bounds.x(), max_bounds.y(), max_bounds.z());
    vertices[6] = Vector3f(max_bounds.x(), min_bounds.y(), max_bounds.z());
    vertices[7] = Vector3f(max_bounds.x(), max_bounds.y(), min_bounds.z());
}

void Model::get_position_bounds()
{
    // if (position.empty())
    // {
    //     // 如果 position 为空，初始化 min_bounds 和 max_bounds 为零向量
    //     min_bounds = Vector3f(0, 0, 0);
    //     max_bounds = Vector3f(0, 0, 0);
    //     return;
    // }

    // // 初始化 min_bounds 和 max_bounds 为第一个顶点的位置
    // min_bounds = position[0];
    // max_bounds = position[0];

    // // 遍历 position 向量，更新 min_bounds 和 max_bounds
    // for (const auto &pos : position)
    // {
    //     min_bounds[0] = std::min(min_bounds.x(), pos.x());
    //     min_bounds[1] = std::min(min_bounds.y(), pos.y());
    //     min_bounds[2] = std::min(min_bounds.z(), pos.z());

    //     max_bounds[0] = std::max(max_bounds.x(), pos.x());
    //     max_bounds[1] = std::max(max_bounds.y(), pos.y());
    //     max_bounds[2] = std::max(max_bounds.z(), pos.z());
    // }
}

/**
 * @brief 加载三角形数据到模型中
 *
 * 该函数通过顶点位置、法线、索引和纹理坐标来加载三角形数据，以构建模型的三角形网格。
 *
 * @param position 顶点位置数组，每个顶点一个Vector3f
 * @param normal 顶点法线数组，每个顶点一个Vector3f
 * @param index 顶点索引数组，每个三角形一个Vector3i，定义了三角形的顶点顺序
 * @param texCrood 纹理坐标数组，每个顶点一个Vector2f，用于映射纹理到三角形
 */
void Model::load_triangles(std::vector<Vector3f> &position, std::vector<Vector3f> normal, std::vector<Vector3i> index, std::vector<Vector2f> texCrood)
{
    // 遍历索引数组，每个索引代表一个三角形的一个顶点
    for (int i = 0; i < index.size(); i++)
    {
        // 创建一个新的三角形对象
        auto temp_triangle = new Triangle();

        // 遍历三角形的三个顶点
        for (int m = 0; m < 3; m++)
        {
            // 设置顶点位置
            temp_triangle->setVertex(m, position[i * 3 + m]);
            // 设置顶点法线
            temp_triangle->setNormal(m, normal[i * 3 + m]);

            // 如果提供了纹理坐标，则设置顶点的纹理坐标
            if (texCrood.size() != 0)
            {
                temp_triangle->setTexCoord(m, texCrood[i * 3 + m][0], texCrood[i * 3 + m][1]);
            }
        }

        // 将构建好的三角形添加到模型的三角形列表中
        this->triangles.push_back(temp_triangle);
    }
}

void Model::Init()
{
    this->set_Transform(Vector3f(1, 1, 1), Vector3f(0, 0, 0), Vector3f(0, 0, 0));
    this->color = Vector3f(100, 100, 240);
    this->filename = filename;
    this->set_color();
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