#pragma once

#include "config.h"

template<typename Derived>
class Application
{
    public:
    Application()
    {
        // Initialize library
        if(!glfwInit())
        {
            std::cerr << "GLFW could not start\n";
            exit(-1);  
        }

        // Instantiate window
        _window = glfwCreateWindow(640, 480, "OpenGL Programming Application", NULL, NULL);
        if(!_window)
        {
            std::cerr << "Failed to create window\n";
            glfwTerminate();
            exit(-1);
        }
        
        // Make window's context current, has to be before loading glad
        glfwMakeContextCurrent(_window);

        if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            glfwTerminate();
            exit(-1);
        }

        
        // Initialize ImGUI
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO();
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
        //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

        // Setup Platform/Renderer backends
        ImGui_ImplGlfw_InitForOpenGL(_window, true);          // Second param install_callback=true will install GLFW callbacks and chain to existing ones.
        ImGui_ImplOpenGL3_Init();
    }

    void StartUp()
    {
        // Set callback function for when the window size is changed
        glfwSetFramebufferSizeCallback(_window, resizeViewport);
        
        static_cast<Derived*>(this)->StartUp();
    }

    void Update()
    {
        static_cast<Derived*>(this)->Update();
    }

    void Run()
    {
        StartUp();

        while(!glfwWindowShouldClose(_window))
        {
            glClearColor(_clearColor.x, _clearColor.y, _clearColor.z, _clearColor.w);
            glClear(GL_COLOR_BUFFER_BIT);

            ImGui_ImplGlfw_NewFrame();
            ImGui_ImplOpenGL3_NewFrame();
            ImGui::NewFrame();

            ImVec2 pos = ImGui::GetCursorScreenPos();
            ImVec2 wSize = ImGui::GetContentRegionAvail();

            glViewport(pos.x, pos.y, wSize.x, wSize.y);

            Update();

            ImGui::Render();
            ImGui_ImplOpenGL3_RenderDrawData(GetDrawData());

            /* Swap front and back buffers */
            glfwSwapBuffers(_window);

            glfwPollEvents();
        }
    }

    ~Application()
    {
        ImGui_ImplGlfw_Shutdown();
        ImGui_ImplOpenGL3_Shutdown();
        ImGui::DestroyContext();
        glfwTerminate();
    }

    ImVec2 GetSize()
    {
        int width, height;
        glfwGetWindowSize(_window, &width, &height);

        return ImVec2(width, height);
    }

    void SetName(const std::string& name)
    {
        glfwSetWindowTitle(_window, name.c_str());
    }

    void SetClearColor(ImVec4 color)
    {
        _clearColor = color;
    }

    protected:
    ImVec4 _clearColor;

    private:
    // Create a window ref
    GLFWwindow* _window;
    
    static void resizeViewport(GLFWwindow* window, int width, int height)
    {
        glViewport(0, 0, width, height);
    }

    static ImDrawData* GetDrawData()
    {
        return ImGui::GetDrawData();
    }
};