#ifndef SANDBOX_SRC_APPLICATION_APPLICATION_H_
#define SANDBOX_SRC_APPLICATION_APPLICATION_H_

#include "main_state.h"

class Application
{
public:
    // Constructors/Destructors
    Application(const Application&) = delete;

    // Operator
    void operator=(Application const&) = delete;

    // Functions
    static void Run();

private:
    // Variables
    GLFWwindow* window_ = nullptr;

    const unsigned int kWindowSizeX_ = 1280, kWindowSizeY_ = 720;

    const char* kWindowTitle_ = "Sandbox";
    const char* kGLSLVersion_ = "#version 130";

    MainState main_state_;

    // Constructor
    Application();

    // Functions
    static Application& Get();

    void IMPLRun();

    void Init();
    void InitWindow();
    void InitImGUI();

    void Update();
    void Render();
};

#endif // SANDBOX_SRC_APPLICATION_APPLICATION_H_
