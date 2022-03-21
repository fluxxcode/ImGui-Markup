#include "sapch.h"
#include "main_state.h"

#include "imgui_markup.h"

void MainState::Update()
{
    ImGui::ShowDemoWindow();

    igm::Print();
}

void MainState::Render()
{ }
