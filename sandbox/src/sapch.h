#ifndef SANDBOX_SRC_SAPCH_H_
#define SANDBOX_SRC_SAPCH_H_

/**
 * @file impch.h
 * @author FluxxCode (info.fluxxcode@gmail.com)
 * @brief Precompiled header for the sandbox application.
 * @copyright Copyright (c) 2022 - 2023
 */

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#define IMGUI_IMPL_OPENGL_LOADER_GLAD
#include "imgui.h"
#include "backends/imgui_impl_opengl3.h"
#include "backends/imgui_impl_glfw.h"

#include <iostream>
#include <vector>
#include <string>
#include <filesystem>

namespace fs = std::filesystem;

#endif  // SANDBOX_SRC_SAPCH_H_
