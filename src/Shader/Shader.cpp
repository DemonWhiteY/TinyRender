#include "Shader.h"

Eigen::Vector3f normal_fragment_shader(const fragment_shader_payload &payload)
{
    Eigen::Vector3f return_color = (payload.normal.head<3>().normalized() + Eigen::Vector3f(1.0f, 1.0f, 1.0f)) / 2.f;
    Eigen::Vector3f result;
    result << return_color.x() * 255, return_color.y() * 255, return_color.z() * 255;
    return result;
}

Eigen::Vector3f phong_fragment_shader(const fragment_shader_payload &payload)
{
    Eigen::Vector3f ka = Eigen::Vector3f(0.005, 0.005, 0.005);
    Eigen::Vector3f kd = payload.color;
    Eigen::Vector3f ks = Eigen::Vector3f(0.7937, 0.7937, 0.7937);

    Eigen::Vector3f amb_light_intensity{20, 20, 20};
    Eigen::Vector3f eye_pos{0, 0, 0};

    float p = 150;

    Eigen::Vector3f color = payload.color;
    Eigen::Vector3f point = payload.view_pos;
    Eigen::Vector3f normal = payload.normal.normalized();

    Eigen::Vector3f result_color = {0, 0, 0};
    Eigen::Vector3f view_dir = (point).normalized();
    for (auto &light : payload.lights)
    {
        // TODO: For each light source in the code, calculate what the *ambient*, *diffuse*, and *specular*
        // components are. Then, accumulate that result on the *result_color* object.
        float rr = (light.position - point).squaredNorm();
        Eigen::Vector3f diffsue(0, 0, 0);
        Eigen::Vector3f specular(0, 0, 0);
        Eigen::Vector3f ambient(0, 0, 0);
        Eigen::Vector3f light_dir = (light.position - point).normalized();

        for (size_t i = 0; i < 3; i++)
        {
            Eigen::Vector3f h = (view_dir + light_dir).normalized(); // half
            float intensity = light.intensity[i] / rr;
            diffsue[i] = kd[i] * intensity * std::max(0.0f, normal.dot(light_dir));
            specular[i] = ks[i] * intensity * std::pow(std::max(0.0f, normal.dot(h)), p);
            ambient[i] = amb_light_intensity[i] * ka[i];
        }
        result_color += diffsue;
        result_color += specular;
        result_color += ambient;
    }

    return result_color * 255.f;
}

Eigen::Vector3f texture_fragment_shader(const fragment_shader_payload &payload)
{
    Eigen::Vector3f return_color = {0, 0, 0};
    if (payload.texture)
    {

        return_color = payload.texture->getColor(payload.tex_coords.x(), payload.tex_coords.y()) / 255.0f;
    }
    else
    {
        return_color = payload.color;
    }

    Eigen::Vector3f ka = Eigen::Vector3f(0.005, 0.005, 0.005);
    Eigen::Vector3f kd = return_color;
    Eigen::Vector3f ks = Eigen::Vector3f(0.7937, 0.7937, 0.7937);

       Eigen::Vector3f amb_light_intensity{20, 20, 20};
    Eigen::Vector3f eye_pos{0, 0, 0};

    float p = 150;

    Eigen::Vector3f color = payload.color;
    Eigen::Vector3f point = payload.view_pos;
    Eigen::Vector3f normal = payload.normal.normalized();

    Eigen::Vector3f result_color = {0, 0, 0};
    Eigen::Vector3f view_dir = (point).normalized();
    for (auto &light : payload.lights)
    {
        // TODO: For each light source in the code, calculate what the *ambient*, *diffuse*, and *specular*
        // components are. Then, accumulate that result on the *result_color* object.
        float rr = (light.position - point).squaredNorm();
        Eigen::Vector3f diffsue(0, 0, 0);
        Eigen::Vector3f specular(0, 0, 0);
        Eigen::Vector3f ambient(0, 0, 0);
        Eigen::Vector3f light_dir = (light.position - point).normalized();

        for (size_t i = 0; i < 3; i++)
        {
            Eigen::Vector3f h = (view_dir + light_dir).normalized(); // half
            float intensity = light.intensity[i] / rr;
            diffsue[i] = kd[i] * intensity * std::max(0.0f, normal.dot(light_dir));
            specular[i] = ks[i] * intensity * std::pow(std::max(0.0f, normal.dot(h)), p);
            ambient[i] = amb_light_intensity[i] * ka[i];
        }
        result_color += diffsue;
        result_color += specular;
        result_color += ambient;

        if (result_color.x() > 1)
        {
            result_color.x() = 1;
        }
        if (result_color.y() > 1)
        {
            result_color.y() = 1;
        }
        if (result_color.z() > 1)
        {
            result_color.z() = 1;
        }
    }

    return result_color * 255.f;
}