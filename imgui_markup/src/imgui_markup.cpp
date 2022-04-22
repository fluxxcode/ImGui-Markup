#include "impch.h"
#include "imgui_markup.h"

/**
 * @file imgui_markup.cpp
 * @author FluxxCode (info.fluxxcode@gmail.com)
 * @brief Implementation of imgui_markup.h
 * @copyright Copyright (c) 2022
 */

#include "parser/parser.h"
#include "common/unit_stack.h"

namespace igm
{

void Print()
{
    // NOTE: This is currently only used for testing purposes

    internal::Unit& unit = internal::UnitStack::CreateEmptyUnit();

    internal::Parser parser(unit);

    parser.ParseFromFile("test.igm");

    for (auto& child : unit.item_tree)
        child->Update();
}

}  // namespace igm
