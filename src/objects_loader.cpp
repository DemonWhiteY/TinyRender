#define TINYOBJLOADER_IMPLEMENTATION
#include "objects_loader.h"

objects_loader::objects_loader(/* args */)
{
}

objects_loader::~objects_loader()
{
}

void objects_loader::load_obj(const std::string &filename, std::vector<Eigen::Vector3f> &positions, std::vector<Eigen::Vector3i> &indices)
{
    tinyobj::ObjReader reader;
    if (!reader.ParseFromFile(filename))
    {
        if (!reader.Error().empty())
        {
            std::cerr << "TinyObjReader: " << reader.Error();
        }
        return;
    }

    auto &attrib = reader.GetAttrib();
    auto &shapes = reader.GetShapes();

    // 读取顶点位置
    for (size_t v = 0; v < attrib.vertices.size() / 3; v++)
    {
        Eigen::Vector3f pos(attrib.vertices[3 * v + 0], attrib.vertices[3 * v + 1], attrib.vertices[3 * v + 2]);
        positions.push_back(pos);
    }

    for (const auto &shape : shapes)
    {
        for (size_t f = 0; f < shape.mesh.num_face_vertices.size(); f++)
        {
            size_t numVertices = shape.mesh.num_face_vertices[f]; // 当前面的顶点数量
            if (numVertices == 3)                                 // 确保面是三角形
            {
                // 获取当前面的三个顶点的索引
                const tinyobj::index_t &index0 = shape.mesh.indices[3 * f + 0];
                const tinyobj::index_t &index1 = shape.mesh.indices[3 * f + 1];
                const tinyobj::index_t &index2 = shape.mesh.indices[3 * f + 2];

                // 存储这三个顶点的索引到 Eigen::Vector3i 中
                Eigen::Vector3i faceIndices(index0.vertex_index, index1.vertex_index, index2.vertex_index);
                indices.push_back(faceIndices); // 将面索引添加到 indices 向量中
            }
        }
    }
}

void objects_loader::load_obj_withoutuv(const std::string &filename, std::vector<Eigen::Vector3f> &positions, std::vector<Eigen::Vector3i> &indices)
{
    tinyobj::ObjReader reader;
    if (!reader.ParseFromFile(filename))
    {
        if (!reader.Error().empty())
        {
            std::cerr << "TinyObjReader: " << reader.Error();
        }
        return;
    }

    auto &attrib = reader.GetAttrib();
    auto &shapes = reader.GetShapes();

    // 读取顶点位置
    for (size_t v = 0; v < attrib.vertices.size() / 3; v++)
    {
        Eigen::Vector3f pos(attrib.vertices[3 * v + 0], attrib.vertices[3 * v + 1], attrib.vertices[3 * v + 2]);
        positions.push_back(pos);
    }

    for (const auto &shape : shapes)
    {
        for (size_t f = 0; f < shape.mesh.num_face_vertices.size(); f++)
        {
            size_t numVertices = shape.mesh.num_face_vertices[f]; // 当前面的顶点数量
            if (numVertices == 3)                                 // 确保面是三角形
            {
                // 获取当前面的三个顶点的索引
                const tinyobj::index_t &index0 = shape.mesh.indices[2 * f + 0];
                const tinyobj::index_t &index1 = shape.mesh.indices[2 * f + 1];
                const tinyobj::index_t &index2 = shape.mesh.indices[2 * f + 2];

                // 存储这三个顶点的索引到 Eigen::Vector3i 中
                Eigen::Vector3i faceIndices(index0.vertex_index, index1.vertex_index, index2.vertex_index);
                indices.push_back(faceIndices); // 将面索引添加到 indices 向量中
            }
        }
    }
}

void objects_loader::load_obj_without_normal(const std::string &filename, std::vector<Eigen::Vector3f> &positions, std::vector<Eigen::Vector3i> &indices)
{
    tinyobj::ObjReader reader;
    if (!reader.ParseFromFile(filename))
    {
        if (!reader.Error().empty())
        {
            std::cerr << "TinyObjReader: " << reader.Error();
        }
        return;
    }

    auto &attrib = reader.GetAttrib();
    auto &shapes = reader.GetShapes();

    // 读取顶点位置
    for (size_t v = 0; v < attrib.vertices.size() / 3; v++)
    {
        Eigen::Vector3f pos(attrib.vertices[3 * v + 0], attrib.vertices[3 * v + 1], attrib.vertices[3 * v + 2]);
        positions.push_back(pos);
    }

    for (const auto &shape : shapes)
    {
        for (const auto &index : shape.mesh.indices)
        {
            Eigen::Vector3i ind(index.vertex_index, index.vertex_index + 1, index.vertex_index + 2);
            indices.push_back(ind);
        }
    }
}
