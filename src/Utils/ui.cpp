#include "ui.h"
/* nuklear - 1.32.0 - public domain */
#include "imgui.h"
#include "imgui_impl_sdl3.h"
#include "imgui_impl_sdlrenderer3.h"
#include <SDL3/SDL.h>
#if defined(IMGUI_IMPL_OPENGL_ES2)
#include <SDL3/SDL_opengles2.h>
#else
#include <SDL3/SDL_opengl.h>
#endif
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

    // Setup SDL
    if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_GAMEPAD))
    {
        printf("Error: SDL_Init(): %s\n", SDL_GetError());
        return;
    }

    // Create window with SDL_Renderer graphics context
    Uint32 window_flags = SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_HIDDEN;
    SDL_Window *window = SDL_CreateWindow("Dear ImGui SDL3+SDL_Renderer example", 1280, 720, window_flags);
    if (window == nullptr)
    {
        printf("Error: SDL_CreateWindow(): %s\n", SDL_GetError());
        return;
    }
    SDL_Renderer *renderer = SDL_CreateRenderer(window, nullptr);
    SDL_SetRenderVSync(renderer, 1);
    if (renderer == nullptr)
    {
        SDL_Log("Error: SDL_CreateRenderer(): %s\n", SDL_GetError());
        return;
    }
    SDL_SetWindowPosition(window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
    SDL_ShowWindow(window);
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

void gui::imageController(SDL_Event event)
{
    if (event.type == SDL_EVENT_KEY_DOWN)
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
}

void gui::windowsStart()
{

    // Create window with SDL_Renderer graphics context
    Uint32 window_flags = SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_HIDDEN;
    SDL_Window *window = SDL_CreateWindow("Dear ImGui SDL3+SDL_Renderer example", 1280, 720, window_flags);
    if (window == nullptr)
    {
        printf("Error: SDL_CreateWindow(): %s\n", SDL_GetError());
        return;
    }
    SDL_Renderer *renderer = SDL_CreateRenderer(window, nullptr);
    SDL_SetRenderVSync(renderer, 1);
    if (renderer == nullptr)
    {
        SDL_Log("Error: SDL_CreateRenderer(): %s\n", SDL_GetError());
        return;
    }
    SDL_SetWindowPosition(window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
    SDL_ShowWindow(window);

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;  // Enable Gamepad Controls

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    // ImGui::StyleColorsLight();

    // Setup Platform/Renderer backends
    ImGui_ImplSDL3_InitForSDLRenderer(window, renderer);
    ImGui_ImplSDLRenderer3_Init(renderer);

    // Load Fonts
    // - If no fonts are loaded, dear imgui will use the default font. You can also load multiple fonts and use ImGui::PushFont()/PopFont() to select them.
    // - AddFontFromFileTTF() will return the ImFont* so you can store it if you need to select the font among multiple.
    // - If the file cannot be loaded, the function will return a nullptr. Please handle those errors in your application (e.g. use an assertion, or display an error and quit).
    // - The fonts will be rasterized at a given size (w/ oversampling) and stored into a texture when calling ImFontAtlas::Build()/GetTexDataAsXXXX(), which ImGui_ImplXXXX_NewFrame below will call.
    // - Use '#define IMGUI_ENABLE_FREETYPE' in your imconfig file to use Freetype for higher quality font rendering.
    // - Read 'docs/FONTS.md' for more instructions and details.
    // - Remember that in C/C++ if you want to include a backslash \ in a string literal you need to write a double backslash \\ !
    // - Our Emscripten build process allows embedding fonts to be accessible at runtime from the "fonts/" folder. See Makefile.emscripten for details.
    // io.Fonts->AddFontDefault();
    // io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\segoeui.ttf", 18.0f);
    // io.Fonts->AddFontFromFileTTF("../../misc/fonts/DroidSans.ttf", 16.0f);
    // io.Fonts->AddFontFromFileTTF("../../misc/fonts/Roboto-Medium.ttf", 16.0f);
    // io.Fonts->AddFontFromFileTTF("../../misc/fonts/Cousine-Regular.ttf", 15.0f);
    // ImFont* font = io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\ArialUni.ttf", 18.0f, nullptr, io.Fonts->GetGlyphRangesJapanese());
    // IM_ASSERT(font != nullptr);

    // Our state
    bool show_demo_window = true;
    bool show_another_window = false;
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

    // Main loop
    bool done = false;
#ifdef __EMSCRIPTEN__
    // For an Emscripten build we are disabling file-system access, so let's not attempt to do a fopen() of the imgui.ini file.
    // You may manually call LoadIniSettingsFromMemory() to load settings from your own storage.
    io.IniFilename = nullptr;
    EMSCRIPTEN_MAINLOOP_BEGIN
#else
    while (!done)
#endif
    {
        // Poll and handle events (inputs, window resize, etc.)
        // You can read the io.WantCaptureMouse, io.WantCaptureKeyboard flags to tell if dear imgui wants to use your inputs.
        // - When io.WantCaptureMouse is true, do not dispatch mouse input data to your main application, or clear/overwrite your copy of the mouse data.
        // - When io.WantCaptureKeyboard is true, do not dispatch keyboard input data to your main application, or clear/overwrite your copy of the keyboard data.
        // Generally you may always pass all inputs to dear imgui, and hide them from your application based on those two flags.
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            ImGui_ImplSDL3_ProcessEvent(&event);
            if (event.type == SDL_EVENT_QUIT)
                done = true;
            if (event.type == SDL_EVENT_WINDOW_CLOSE_REQUESTED && event.window.windowID == SDL_GetWindowID(window))
                done = true;
        }
        if (SDL_GetWindowFlags(window) & SDL_WINDOW_MINIMIZED)
        {
            SDL_Delay(10);
            continue;
        }

        // Start the Dear ImGui frame
        ImGui_ImplSDLRenderer3_NewFrame();
        ImGui_ImplSDL3_NewFrame();
        ImGui::NewFrame();

        // 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).
        if (show_demo_window)
            ImGui::ShowDemoWindow(&show_demo_window);

        // 2. Show a simple window that we create ourselves. We use a Begin/End pair to create a named window.
        {
            static float f = 0.0f;
            static int counter = 0;

            ImGui::Begin("Hello, world!"); // Create a window called "Hello, world!" and append into it.

            ImGui::Text("This is some useful text.");          // Display some text (you can use a format strings too)
            ImGui::Checkbox("Demo Window", &show_demo_window); // Edit bools storing our window open/close state
            ImGui::Checkbox("Another Window", &show_another_window);

            ImGui::SliderFloat("float", &f, 0.0f, 1.0f);             // Edit 1 float using a slider from 0.0f to 1.0f
            ImGui::ColorEdit3("clear color", (float *)&clear_color); // Edit 3 floats representing a color

            if (ImGui::Button("Button")) // Buttons return true when clicked (most widgets return true when edited/activated)
                counter++;
            ImGui::SameLine();
            ImGui::Text("counter = %d", counter);

            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
            ImGui::End();
        }

        // 3. Show another simple window.
        if (show_another_window)
        {
            ImGui::Begin("Another Window", &show_another_window); // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
            ImGui::Text("Hello from another window!");
            if (ImGui::Button("Close Me"))
                show_another_window = false;
            ImGui::End();
        }

        // Rendering
        ImGui::Render();
        // SDL_RenderSetScale(renderer, io.DisplayFramebufferScale.x, io.DisplayFramebufferScale.y);
        SDL_SetRenderDrawColorFloat(renderer, clear_color.x, clear_color.y, clear_color.z, clear_color.w);
        SDL_RenderClear(renderer);
        ImGui_ImplSDLRenderer3_RenderDrawData(ImGui::GetDrawData(), renderer);
        SDL_RenderPresent(renderer);
    }
#ifdef __EMSCRIPTEN__
    EMSCRIPTEN_MAINLOOP_END;
#endif

    // Cleanup
    ImGui_ImplSDLRenderer3_Shutdown();
    ImGui_ImplSDL3_Shutdown();
    ImGui::DestroyContext();

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

gui::~gui()
{
}
