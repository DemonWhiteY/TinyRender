#ifndef RASTERIZER_TEXTURE_H
#define RASTERIZER_TEXTURE_H

#include <string>
#include <vector>
#include <Eigen/Eigen>
#include <iostream>
#include "stb_image.h"

template <typename T>
T clamp(T value, T min_value, T max_value)
{
    return (value < min_value) ? min_value : (value > max_value) ? max_value
                                                                 : value;
}

class Texture
{
private:
    unsigned char *image_data;
    int width, height, channels;

public:
    Texture()
    {
        // 你可以在这里提供默认的路径或初始化
        image_data = nullptr;
    }
    Texture(const std::string &filename)
    {
        image_data = stbi_load(filename.c_str(), &width, &height, &channels, STBI_rgb);
        if (!image_data)
        {
            throw std::runtime_error("Failed to load texture");
        }
    }

    ~Texture()
    {
        stbi_image_free(image_data);
    }

    Eigen::Vector3f getColor(float u, float v)
    {
        // Clamp u and v to [0, 1]
        u = clamp(u, 0.0f, 1.0f);
        v = clamp(v, 0.0f, 1.0f);

        // Calculate the image coordinates
        int x = static_cast<int>(u * width);
        int y = static_cast<int>((1 - v) * height);

        // Ensure x and y are within bounds
        x = clamp(x, 0, width - 1);
        y = clamp(y, 0, height - 1);

        // Calculate the index of the pixel in the image data
        int index = (y * width + x) * 3;
        unsigned char r = image_data[index];
        unsigned char g = image_data[index + 1];
        unsigned char b = image_data[index + 2];

        return Eigen::Vector3f(r, g, b);
    }
};

#endif // RASTERIZER_TEXTURE_H
