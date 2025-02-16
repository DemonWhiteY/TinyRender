#include "ui.h"
/* nuklear - 1.32.0 - public domain */
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdarg.h>
#include <string.h>
#include <math.h>
#include <assert.h>
#include <limits.h>
#include <time.h>

#define NK_INCLUDE_FIXED_TYPES
#define NK_INCLUDE_STANDARD_IO
#define NK_INCLUDE_STANDARD_VARARGS
#define NK_INCLUDE_DEFAULT_ALLOCATOR
#define NK_INCLUDE_VERTEX_BUFFER_OUTPUT
#define NK_INCLUDE_FONT_BAKING
#define NK_INCLUDE_DEFAULT_FONT
#define NK_IMPLEMENTATION
#include "nuklear.h"
#define NK_SDL_RENDERER_IMPLEMENTATION
#include "nuklear_sdl_renderer.h"

#define WINDOW_WIDTH 1200
#define WINDOW_HEIGHT 800

Eigen::Vector3f rotateY(const Eigen::Vector3f &v, float angle)
{
    Eigen::Matrix3f rotationMatrix;
    rotationMatrix = Eigen::AngleAxisf(angle, Eigen::Vector3f::UnitY());
    return rotationMatrix * v;
}

Eigen::Vector3f rotateX(const Eigen::Vector3f &v, float angle)
{
    Eigen::Matrix3f rotationMatrix;
    rotationMatrix = Eigen::AngleAxisf(angle, Eigen::Vector3f::UnitX());
    return rotationMatrix * v;
}
gui::gui(int width, int height)
{

    this->width = width;
    this->height = height;
    window = SDL_CreateWindow("Hello, SDL3!", width, height, SDL_WINDOW_RESIZABLE);
    if (!window)
    {
        SDL_Log("Could not create a window: %s", SDL_GetError());
        return;
    }

    SDL_SetWindowPosition(window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);

    renderer = SDL_CreateRenderer(window, nullptr);
    if (!renderer)
    {
        SDL_Log("Create renderer failed: %s", SDL_GetError());
        return;
    }

    updateSurface();

    struct nk_context *ctx = nk_sdl_init(window, renderer);
    struct nk_font_atlas *atlas;
    nk_sdl_font_stash_begin(&atlas);
    nk_sdl_font_stash_end();
}

void gui::updateSurface()
{
    SDL_Surface *surface = SDL_LoadBMP("../output/output.bmp");
    if (!surface)
    {
        std::cerr << "加载 BMP 文件失败: " << SDL_GetError() << std::endl;
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return;
    }

    // 创建纹理
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_DestroySurface(surface); // 不再需要 surface 了，可以释放它

    if (!texture)
    {
        std::cerr << "创建纹理失败: " << SDL_GetError() << std::endl;
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return;
    }
}

void gui::windowsStart()
{
    type Type = type::READ;
    int model_num = -1;
    bool running = true;
    bool isMouseDown = false;
    bool isCtrlDown = false;
    int mouseX, mouseY;
    SDL_Event event;
    while (running)
    {
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_EVENT_QUIT)
            {
                running = false;
            }
            else if (event.type == SDL_EVENT_KEY_DOWN)
            {
                if (event.key.key == SDLK_LCTRL)
                {
                    isCtrlDown = true;
                }
                else if (event.key.key == SDLK_F1)
                {
                    Type = type::READ;
                }
                else if (event.key.key == SDLK_F2)
                {
                    Type = type::EDIT;
                }
                else if (event.type == SDL_EVENT_KEY_UP)
                {
                    if (event.key.key == SDLK_LCTRL)
                    {
                        isCtrlDown = false;
                    }
                }
            }

            else if (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN)
            {
                // 检测鼠标按下事件
                if (event.button.button == SDL_BUTTON_LEFT) // 左键按下
                {
                    isMouseDown = true;
                    mouseX = event.button.x;
                    mouseY = event.button.y;
                    model_num = ras->get_pixel_model(event.motion.x, event.motion.y);
                    std::cout << "Mouse at:" << ras->get_pixel_model(event.motion.x, event.motion.y) << std::endl;
                }
            }
            else if (event.type == SDL_EVENT_MOUSE_BUTTON_UP)
            {
                // 检测鼠标释放事件
                if (event.button.button == SDL_BUTTON_LEFT) // 左键释放
                {
                    isMouseDown = false;

                    std::cout << "Mouse button up at: (" << event.button.x << ", " << event.button.y << ")" << std::endl;
                }
            }

            // 只读模式
            else if (Type == type::READ)
            {

                if (event.type == SDL_EVENT_MOUSE_MOTION)
                {
                    // 检测鼠标移动事件
                    if (isMouseDown) // 如果鼠标处于按下状态
                    {

                        auto &camera = ras->get_camera();
                        auto position = camera.get_position();
                        auto up = camera.get_up();
                        auto target = camera.get_target();
                        if (isCtrlDown)
                        {
                            float deltaX = (event.motion.x - mouseX) * 0.01f; // 水平旋转角度
                            float deltaY = (event.motion.y - mouseY) * 0.01f; // 垂直旋转角度

                            // 计算新的摄像机方向
                            Vector3f direction = target - position;
                            direction = rotateY(direction, deltaY); // 绕Y轴旋转
                            direction = rotateX(direction, deltaX); // 绕X轴旋转

                            // 更新摄像机目标点
                            target = position + direction;
                        }
                        else
                        {
                            position += Vector3f(event.motion.x - mouseX, mouseY - event.motion.y, 0) * -0.01;
                            target += Vector3f(event.motion.x - mouseX, mouseY - event.motion.y, 0) * -0.01;
                        }
                        camera.set_position(position, up, target);
                        ras->clear();
                        ras->Handle();
                        ras->output();
                        updateSurface();
                        mouseX = event.motion.x;
                        mouseY = event.motion.y;
                    }
                }

                else if (event.type == SDL_EVENT_MOUSE_WHEEL)
                {

                    int z = event.wheel.y; // 垂直滚动的距离

                    auto &camera = ras->get_camera();
                    auto position = camera.get_position();
                    auto up = camera.get_up();
                    auto target = camera.get_target();
                    camera.set_position(position + Vector3f(0, 0, z), up, target);
                    ras->clear();
                    ras->Handle();
                    ras->output();
                    updateSurface();
                }
            }

            // 编辑模式
            else if (Type == type::EDIT)
            {

                if (event.type == SDL_EVENT_MOUSE_MOTION)
                {
                    // 检测鼠标移动事件
                    if (isMouseDown && model_num != -1) // 如果鼠标处于按下状态
                    {
                        auto &model = ras->get_models()[model_num];
                        if (isCtrlDown)
                        {
                            float deltaX = (event.motion.x - mouseX) * 0.01f; // 水平旋转角度
                            float deltaY = (event.motion.y - mouseY) * 0.01f; // 垂直旋转角度
                            // 计算新的摄像机方向
                        }
                        else
                        {
                            model.translate += Vector3f(event.motion.x - mouseX, mouseY - event.motion.y, 0) * 0.01;
                        }
                        ras->clear();
                        ras->Handle();
                        ras->output();
                        updateSurface();
                        mouseX = event.motion.x;
                        mouseY = event.motion.y;
                    }
                }

                else if (event.type == SDL_EVENT_MOUSE_WHEEL)
                {

                    int z = event.wheel.y; // 垂直滚动的距离

                    ras->clear();
                    ras->Handle();
                    ras->output();
                    updateSurface();
                }
            }
            nk_sdl_handle_event(&event);
        }
        nk_sdl_render(NK_ANTI_ALIASING_ON);

        // 清空渲染器
        SDL_RenderClear(renderer);

        // 渲染纹理到窗口
        SDL_RenderTexture(renderer, texture, NULL, NULL);

        // 显示渲染器内容
        SDL_RenderPresent(renderer);
    }

    // 清理资源
    nk_sdl_shutdown();
    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

gui::~gui()
{
}
