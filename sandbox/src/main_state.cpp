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
    igm::Print();
}

void MainState::Update()
{
    ImGui::ShowDemoWindow();
}

void MainState::Render()
{ }
