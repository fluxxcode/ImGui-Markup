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
    this->test_unit = igm::ParseFromFile(igm::UnitType::kGUI,
                                         "examples/main.igm", &result);
    if (!result)
        std::cerr << igm::GetLastResult(this->test_unit).message << std::endl;

    this->theme_unit = igm::ParseFromFile(igm::UnitType::kTheme,
                                         "examples/themes.igm", &result);
    if (!result)
        std::cerr << igm::GetLastResult(this->theme_unit).message << std::endl;

    igm::InitUnitTheme(this->test_unit, this->theme_unit, "dark");
}

void MainState::Update()
{
    igm::Update(this->test_unit);
}

void MainState::Render()
{ }

void MainState::CheckIsPressed(std::string item_id)
{
    if (igm::IsItemPressed(this->test_unit, item_id.c_str()))
        std::cout << "PRESSED: " << item_id << std::endl;
}

void MainState::CheckIsHovered(std::string item_id)
{
    if (igm::IsItemHovered(this->test_unit, item_id.c_str()))
        std::cout << "HOVERED: " << item_id << std::endl;
}
