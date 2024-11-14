#define TINYOBJLOADER_IMPLEMENTATION
#include "objects_loader.h"

objects_loader::objects_loader(/* args */)
{
}

objects_loader::~objects_loader()
{
}

void objects_loader::load_obj(const std::string &filename, std::vector<Eigen::Vector3f> &positions, std::vector<Eigen::Vector3i> &indices, std::vector<Eigen::Vector3f> &normal, std::vector<Eigen::Vector2f> &uv)
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

    for (const auto &shape : shapes)
    {
        // 遍历每个面片索引
        size_t index_offset = 0;
        for (size_t f = 0; f < shape.mesh.num_face_vertices.size(); f++)
        {
            // 每个面应该有3个顶点
            Eigen::Vector3i face_indices;

            for (size_t v = 0; v < 3; v++)
            {
                // 顶点索引
                tinyobj::index_t idx = shape.mesh.indices[index_offset + v];

                // 获取顶点位置
                int vertex_index = idx.vertex_index;
                Eigen::Vector3f pos(
                    attrib.vertices[3 * vertex_index + 0],
                    attrib.vertices[3 * vertex_index + 1],
                    attrib.vertices[3 * vertex_index + 2]);
                positions.push_back(pos);

                // 获取法线
                if (idx.normal_index >= 0)
                {
                    int normal_index = idx.normal_index;
                    Eigen::Vector3f norm(
                        attrib.normals[3 * normal_index + 0],
                        attrib.normals[3 * normal_index + 1],
                        attrib.normals[3 * normal_index + 2]);
                    normal.push_back(norm);
                }

                // 获取UV坐标
                if (idx.texcoord_index >= 0)
                {
                    int texcoord_index = idx.texcoord_index;
                    Eigen::Vector2f uv_coord(
                        attrib.texcoords[2 * texcoord_index + 0],
                        attrib.texcoords[2 * texcoord_index + 1]);
                    uv.push_back(uv_coord);
                }

                // 添加到面片索引中
                face_indices[v] = positions.size() - 1;
            }
            indices.push_back(face_indices);
            index_offset += 3; // 每个面片3个顶点
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
