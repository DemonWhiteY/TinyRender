#include "ui.h"
/* nuklear - 1.32.0 - public domain */

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
}

void gui::updateSurface()
{
    ras->clear();
    ras->Handle();
    ras->output();
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

    // Create window with SDL_Renderer graphics context
    Uint32 window_flags = SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_HIDDEN | SDL_WINDOW_MAXIMIZED;
    window = SDL_CreateWindow("Dear ImGui SDL3+SDL_Renderer example", 1680, 920, window_flags);
    if (window == nullptr)
    {
        printf("Error: SDL_CreateWindow(): %s\n", SDL_GetError());
        return;
    }

    renderer = SDL_CreateRenderer(window, nullptr);
    SDL_SetRenderVSync(renderer, 1);
    if (renderer == nullptr)
    {
        SDL_Log("Error: SDL_CreateRenderer(): %s\n", SDL_GetError());
        return;
    }
    SDL_SetWindowPosition(window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
    SDL_ShowWindow(window);
    updateSurface();
    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;  // Enable Gamepad Controls
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;     // 启用 Docking
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
    io.Fonts->AddFontFromFileTTF("../fonts/DroidSans.ttf", 20.0f);
    // io.Fonts->AddFontFromFileTTF("../../misc/fonts/Roboto-Medium.ttf", 16.0f);
    // io.Fonts->AddFontFromFileTTF("../../misc/fonts/Cousine-Regular.ttf", 15.0f);
    // ImFont* font = io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\ArialUni.ttf", 18.0f, nullptr, io.Fonts->GetGlyphRangesJapanese());
    // IM_ASSERT(font != nullptr);

    // Our state
    bool show_demo_window = true;
    bool show_another_window = true;
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

        ImGuiViewport *viewport = ImGui::GetMainViewport();
        ImGui::SetNextWindowPos(viewport->WorkPos);
        ImGui::SetNextWindowSize(viewport->WorkSize);
        ImGui::SetNextWindowViewport(viewport->ID);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
        ImGui::Begin("DockSpace", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus | ImGuiWindowFlags_MenuBar);
        ImGui::PopStyleVar(3);

        // 创建 DockSpace ID
        ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
        ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), ImGuiDockNodeFlags_PassthruCentralNode);
        ImGui::End();
        imageController();
        showMainMeauBar();
        showRender();
        showSencePanel();
        showObjectPanel();
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

void gui::showRender()
{
    ImGui::Begin("Render", nullptr,
                 ImGuiWindowFlags_NoCollapse |
                     ImGuiWindowFlags_NoScrollbar); // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)

    // 获取窗口的大小
    ImVec2 windowSize = ImGui::GetWindowSize();
    // 设置图片的初始大小
    ImVec2 imageSize(400, 400); // 设置图片显示大小
    // 计算图片居中的位置
    ImVec2 imagePos = ImVec2((windowSize.x - imageSize.x) * 0.5f, (windowSize.y - imageSize.y) * 0.5f);

    ImTextureID user_texture_id = 0;
    user_texture_id = (ImTextureID)texture; // 将SDL_Texture指针转换为ImTextureID

    // 保存当前的光标位置
    ImVec2 cursorPos = ImGui::GetCursorPos();
    // 设置光标位置到图片居中的位置
    ImGui::SetCursorPos(imagePos);
    // 渲染图片
    ImGui::Image(user_texture_id, imageSize);

    // 恢复光标位置
    ImGui::SetCursorPos(cursorPos);

    // 在窗口的右下角添加缩放输入框
    static float scale = 1.0f;                                       // 缩放比例
    ImVec2 inputPos = ImVec2(windowSize.x - 150, windowSize.y - 40); // 调整位置以适应输入框大小

    ImGui::SetCursorPos(inputPos);

    ImGui::InputFloat("Scale", &scale, 0.1f, 1.0f, "%.2f");

    // 根据缩放比例调整图片大小
    ImVec2 scaledImageSize(imageSize.x * scale, imageSize.y * scale);
    imagePos = ImVec2((windowSize.x - scaledImageSize.x) * 0.5f, (windowSize.y - scaledImageSize.y) * 0.5f);
    ImGui::SetCursorPos(imagePos);
    ImGui::Image(user_texture_id, scaledImageSize);

    ImGui::End();
}

void gui::showObjectPanel()
{
    ImGui::Begin("Object Panel", nullptr,
                 ImGuiWindowFlags_NoCollapse |
                     ImGuiWindowFlags_NoScrollbar);
    switch (object_type)
    {
    case 0:
        modelInfo();
        break;

    default:

        break;
    }

    ImGui::End();
}

void gui::modelInfo()
{

    {

        auto &model = ras->get_models()[model_num];
        ImGui::Text("position:");
        if (ImGui::BeginTable("PositionTable", 3, ImGuiTableFlags_BordersInnerH | ImGuiTableFlags_Resizable))
        {
            ImGui::TableNextColumn();
            ImGui::InputFloat("X", &model.translate[0], 0.1f, 1.0f, "%.2f");
            ImGui::TableNextColumn();
            ImGui::InputFloat("Y", &model.translate[1], 0.1f, 1.0f, "%.2f");
            ImGui::TableNextColumn();
            ImGui::InputFloat("Z", &model.translate[2], 0.1f, 1.0f, "%.2f");
            ImGui::EndTable();
        }

        ImGui::Text("Scale:");
        if (ImGui::BeginTable("ScaleTable", 3, ImGuiTableFlags_BordersInnerH | ImGuiTableFlags_Resizable))
        {
            ImGui::TableNextColumn();
            ImGui::InputFloat("X", &model.scale[0], 0.1f, 1.0f, "%.2f");
            ImGui::TableNextColumn();
            ImGui::InputFloat("Y", &model.scale[1], 0.1f, 1.0f, "%.2f");
            ImGui::TableNextColumn();
            ImGui::InputFloat("Z", &model.scale[2], 0.1f, 1.0f, "%.2f");
            ImGui::EndTable();
        }

        ImGui::Text("Rotation:");
        if (ImGui::BeginTable("RotationTable", 3, ImGuiTableFlags_BordersInnerH | ImGuiTableFlags_Resizable))
        {
            ImGui::TableNextColumn();
            ImGui::InputFloat("X", &model.rotation[0], 0.1f, 1.0f, "%.2f");
            ImGui::TableNextColumn();
            ImGui::InputFloat("Y", &model.rotation[1], 0.1f, 1.0f, "%.2f");
            ImGui::TableNextColumn();
            ImGui::InputFloat("Z", &model.rotation[2], 0.1f, 1.0f, "%.2f");
            ImGui::EndTable();
        }
    }
}

void gui::showSencePanel()
{
    ImGui::Begin("Scene Panel", nullptr,
                 ImGuiWindowFlags_NoCollapse |
                     ImGuiWindowFlags_NoScrollbar);
    // 显示模型列表
    if (ImGui::CollapsingHeader("Models", ImGuiTreeNodeFlags_DefaultOpen))
    {
        auto &models = ras->get_models();
        auto &lights = ras->get_lights();
        if (models.empty())
        {
            ImGui::Text("No models in scene");
        }
        else
        {
            for (size_t i = 0; i < models.size(); ++i)
            {
                if (ImGui::TreeNode((void *)(intptr_t)i, ras->get_models()[i].name.c_str()))
                {
                    model_num = i;
                    object_type = 0;
                    ImGui::TreePop();
                }
            }
            for (size_t i = models.size(); i < lights.size() + models.size(); ++i)
            {
                if (ImGui::TreeNode((void *)(intptr_t)i, "Light %d", i))
                {
                    model_num = i;
                    object_type = 1;
                    ImGui::TreePop();
                }
            }
        }
    }

    ImGui::End();
}

void gui::showMainMeauBar()
{
    if (ImGui::BeginMainMenuBar())
    {
        if (ImGui::BeginMenu("File"))
        {

            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("Edit"))
        {
            if (ImGui::MenuItem("Undo", "CTRL+Z"))
            {
            }
            if (ImGui::MenuItem("Redo", "CTRL+Y", false, false))
            {
            } // Disabled item
            ImGui::Separator();
            if (ImGui::MenuItem("Cut", "CTRL+X"))
            {
            }
            if (ImGui::MenuItem("Copy", "CTRL+C"))
            {
            }
            if (ImGui::MenuItem("Paste", "CTRL+V"))
            {
            }
            ImGui::EndMenu();
        }
        ImGui::EndMainMenuBar();
    }
}
void gui::imageController()
{
    // 检测 Ctrl 键按下和释放
    if (ImGui::IsKeyDown(ImGuiKey_LeftCtrl))
    {
        isCtrlDown = true;
    }
    else
    {
        isCtrlDown = false;
    }

    // 检测 F1 和 F2 键按下
    if (ImGui::IsKeyPressed(ImGuiKey_F1))
    {
        Type = type::READ;
    }
    else if (ImGui::IsKeyPressed(ImGuiKey_F2))
    {
        Type = type::EDIT;
    }

    // 检测鼠标按下事件
    if (ImGui::IsMouseClicked(ImGuiMouseButton_Left))
    {
        isMouseDown = true;
        ImVec2 mousePos = ImGui::GetMousePos();
        mouseX = mousePos.x;
        mouseY = mousePos.y;
        model_num = ras->get_pixel_model(mouseX, mouseY);
        std::cout << "Mouse at:" << model_num << std::endl;
    }

    // 检测鼠标释放事件
    if (ImGui::IsMouseReleased(ImGuiMouseButton_Left))
    {
        isMouseDown = false;
        ImVec2 mousePos = ImGui::GetMousePos();
        std::cout << "Mouse button up at: (" << mousePos.x << ", " << mousePos.y << ")" << std::endl;
    }

    // 只读模式
    if (Type == type::READ)
    {
        // 检测鼠标移动事件
        if (isMouseDown)
        {
            ImVec2 mousePos = ImGui::GetMousePos();
            float deltaX = (mousePos.x - mouseX) * 0.01f; // 水平旋转角度
            float deltaY = (mousePos.y - mouseY) * 0.01f; // 垂直旋转角度

            auto &camera = ras->get_camera();
            auto position = camera.get_position();
            auto up = camera.get_up();
            auto target = camera.get_target();

            if (isCtrlDown)
            {
                // 计算新的摄像机方向
                Vector3f direction = target - position;
                direction = rotateY(direction, deltaY); // 绕Y轴旋转
                direction = rotateX(direction, deltaX); // 绕X轴旋转

                // 更新摄像机目标点
                target = position + direction;
            }
            else
            {
                position += Vector3f(deltaX, -deltaY, 0) * 10.0f; // 调整移动速度
                target += Vector3f(deltaX, -deltaY, 0) * 10.0f;   // 调整移动速度
            }

            camera.set_position(position, up, target);

            updateSurface();
            mouseX = mousePos.x;
            mouseY = mousePos.y;
        }

        // 检测鼠标滚轮事件
        float wheelDelta = ImGui::GetIO().MouseWheel;
        if (wheelDelta != 0.0f)
        {
            auto &camera = ras->get_camera();
            auto position = camera.get_position();
            auto up = camera.get_up();
            auto target = camera.get_target();

            // 调整滚动速度
            float zoomSpeed = 10.0f;
            position += Vector3f(0, 0, wheelDelta * zoomSpeed);
            target += Vector3f(0, 0, wheelDelta * zoomSpeed);

            camera.set_position(position, up, target);

            updateSurface();
        }
    }

    // 编辑模式
    else if (Type == type::EDIT)
    {
        // 检测鼠标移动事件
        if (isMouseDown && model_num != -1)
        {
            ImVec2 mousePos = ImGui::GetMousePos();
            float deltaX = (mousePos.x - mouseX) * 0.01f; // 水平旋转角度
            float deltaY = (mousePos.y - mouseY) * 0.01f; // 垂直旋转角度

            auto &model = ras->get_models()[model_num];

            if (isCtrlDown)
            {
                // 计算新的模型旋转
                // 这里可以根据需要添加旋转逻辑
            }
            else
            {
                model.translate += Vector3f(deltaX, -deltaY, 0) * 10.0f; // 调整移动速度
            }

            updateSurface();
            mouseX = mousePos.x;
            mouseY = mousePos.y;
        }

        // 检测鼠标滚轮事件
        float wheelDelta = ImGui::GetIO().MouseWheel;
        if (wheelDelta != 0.0f)
        {

            updateSurface();
        }
    }
}