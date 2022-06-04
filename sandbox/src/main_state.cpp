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
    this->test_unit = igm::ParseFromFile("examples/main.igm", &result);

    const igm::Result ret = igm::GetLastResult(this->test_unit);

    if (!result)
        std::cerr << ret.message << std::endl;

}

void MainState::Update()
{
    igm::Update(this->test_unit);
}

void MainState::Render()
{ }
