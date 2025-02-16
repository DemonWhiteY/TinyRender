#ifndef UI_H
#define UI_H
#include "../rasterizer.h"
#include "SDL3/SDL.h"
#include "SDL3_ttf/SDL_ttf.h"
#include <iostream>
#include "../Sence/Camera.h"
#include <Eigen/Geometry>
enum class type
{
    READ,
    EDIT
};

class gui
{
private:
    int width = 800;
    int height = 600;
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Texture *texture;
    Rasterizer *ras;

public:
    gui();
    gui(int width, int height);
    ~gui();
    void updateSurface();
    void windowsStart();
    void get_rasterizer(Rasterizer *rasterizer)
    {
        this->ras = rasterizer;
    }
};

#endif
