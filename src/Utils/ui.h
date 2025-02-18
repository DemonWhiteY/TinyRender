#ifndef UI_H
#define UI_H
#include <stdio.h>
#include <shobjidl.h> // 包含 IFileDialog 接口的定义
#include <comdef.h>   // 包含 COM 对象的定义
#include "imgui.h"
#include "imgui_impl_sdl3.h"
#include "imgui_impl_sdlrenderer3.h"
#include "imgui_impl_opengl3.h"
#include <SDL3/SDL.h>
#include "SDL3_image/SDL_image.h"
#include "../Texture.h"
#if defined(IMGUI_IMPL_OPENGL_ES2)
#include <SDL3/SDL_opengles2.h>
#else
#include <SDL3/SDL_opengl.h>
#endif
#include "../rasterizer.h"
#include "SDL3_ttf/SDL_ttf.h"
#include <iostream>
#include "../Sence/Camera.h"
#include <Eigen/Geometry>
#include "json_loader.h"
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
    struct nk_context *ctx;

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

    void imageController();
    type Type = type::READ;
    int model_id = -1;
    int object_type = -1;
    int model_num = -1;
    bool running = true;
    bool isMouseDown = false;
    bool isCtrlDown = false;
    int mouseX, mouseY;
    SDL_Event event;
    ImVec2 windowSize;
    ImVec2 windowPos;
    ImVec2 imagePos;
    ImVec2 scaledImageSize;
    void showMainMeauBar();
    void showRender();
    void showSencePanel();
    void showObjectPanel();
    void modelInfo();
    void lightInfo();
    void TextureInfo();
    void MaterialInfo();
    ImVec2 translationPosition(ImVec2 pos);
};

#endif
