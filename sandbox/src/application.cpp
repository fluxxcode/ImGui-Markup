#include "sapch.h"
#include "application.h"

/**
 * @file application.cpp
 * @author FluxxCode (info.fluxxcode@gmail.com)
 * @brief Implementation of application.h
 * @copyright Copyright (c) 2022 - 2023
 */

void Application::Run()
{
    Application::Get().IMPLRun();
}

Application::Application()
{ }

Application& Application::Get()
{
    static Application instance;
    return instance;
}

void Application::IMPLRun()
{
    this->Init();

    while (!glfwWindowShouldClose(this->window_))
    {
        this->Update();
        this->Render();
    }
}

void Application::Init()
{
    this->InitWindow();
    this->InitImGUI();
}

void Application::InitWindow()
{
    if (glfwInit() != GLFW_TRUE)
        std::cerr << "Unable to init glfw" << std::endl;

    this->window_ = glfwCreateWindow(this->kWindowSizeX_, this->kWindowSizeY_,
                                     this->kWindowTitle_, NULL, NULL);

    int code = glfwGetError(nullptr);

    if (!this->window_)
        std::cerr << "Unable to create window: " << code << std::endl;

    glfwMakeContextCurrent(this->window_);

    // Init Glad
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
}

void Application::InitImGUI()
{
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;

    // Set default style
    ImGui::StyleColorsDark();

    ImGui_ImplGlfw_InitForOpenGL(this->window_, true);
    ImGui_ImplOpenGL3_Init(this->kGLSLVersion_);

    ImGui::GetIO().IniFilename = nullptr;
}

void Application::Update()
{
    glfwPollEvents();

    // Render ImGui
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    this->main_state_.Update();
}

void Application::Render()
{
    glClear(GL_COLOR_BUFFER_BIT);

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    this->main_state_.Render();

    glfwSwapBuffers(this->window_);
}
