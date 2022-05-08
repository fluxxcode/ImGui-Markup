#include "sapch.h"
#include "main_state.h"

/**
 * @file main_state.cpp
 * @author FluxxCode (info.fluxxcode@gmail.com)
 * @brief Implementation of main_state.h
 * @copyright Copyright (c) 2022
 */

#include "imgui_markup.h"

MainState::MainState()
{
    bool result;
    size_t unit_id = igm::ParseFromFile("test.igm", &result);

    const igm::Result ret = igm::GetLastResult(unit_id);

    if (!result)
        std::cerr << ret.message << std::endl;
}

void MainState::Update()
{
    ImGui::ShowDemoWindow();
}

void MainState::Render()
{ }
