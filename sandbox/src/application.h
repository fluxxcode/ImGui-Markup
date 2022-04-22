#ifndef SANDBOX_SRC_APPLICATION_APPLICATION_H_
#define SANDBOX_SRC_APPLICATION_APPLICATION_H_

/**
 * @file application.h
 * @author FluxxCode (info.fluxxcode@gmail.com)
 * @brief Contains main application class.
 * @copyright Copyright (c) 2022
 */

#include "main_state.h"

class Application
{
public:
    Application(const Application&) = delete;

    void operator=(Application const&) = delete;

    static void Run();

private:
    GLFWwindow* window_ = nullptr;

    const unsigned int kWindowSizeX_ = 1280, kWindowSizeY_ = 720;

    const char* kWindowTitle_ = "Sandbox";
    const char* kGLSLVersion_ = "#version 130";

    MainState main_state_;

    Application();

    static Application& Get();

    void IMPLRun();

    void Init();
    void InitWindow();
    void InitImGUI();

    void Update();
    void Render();
};

#endif // SANDBOX_SRC_APPLICATION_APPLICATION_H_
