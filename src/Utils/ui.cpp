#include "ui.h"
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
    bool running = true;
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
                if (event.key.key == SDLK_A)
                {
                    auto &models = ras->get_models(); // 获取 models 的引用
                    for (auto &model : models)        // 使用引用修改元素
                    {
                        model.rotation[1] += 40;
                    }
                    ras->clear();
                    ras->Handle();
                    ras->output();
                    updateSurface();
                }
            }
        }

        // 清空渲染器
        SDL_RenderClear(renderer);

        // 渲染纹理到窗口
        SDL_RenderTexture(renderer, texture, NULL, NULL);

        // 显示渲染器内容
        SDL_RenderPresent(renderer);
    }

    // 清理资源
    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

gui::~gui()
{
}
