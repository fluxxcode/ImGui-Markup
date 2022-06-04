#include "impch.h"
#include "imgui_markup.h"

/**
 * @file imgui_markup.cpp
 * @author FluxxCode (info.fluxxcode@gmail.com)
 * @brief Implementation of imgui_markup.h
 * @copyright Copyright (c) 2022
 */

#include "common/unit_stack.h"
#include "parser/parser.h"
#include "parser/parser_result.h"

#include "attribute_types/base_types/vector2.h"

namespace igm
{

size_t ParseFromFile(const char* path, bool* result_out)
{
    if (result_out)
        *result_out = false;

    internal::Unit& unit = internal::UnitStack::CreateEmptyUnit();
    internal::Parser parser(unit);

    const internal::ParserResult result = parser.ParseFromFile(path);
    if (result.type != internal::ParserResultType::kSuccess)
    {
        internal::UnitStack::SetLastResult(unit.unit_id,
            Result(ResultType::kParserError, result.ToString()));

        return unit.unit_id;
    }

    if (result_out)
        *result_out = true;

    return unit.unit_id;
}

void DeleteUnit(size_t unit, bool* result)
{
    internal::UnitStack::DeleteUnit(unit, result);
}

Result GetLastResult(size_t unit, bool* result)
{
    return internal::UnitStack::GetLastResult(unit, result);
}

void Update(size_t unit_id, size_t display_width, size_t display_height,
            bool* result)
{
    internal::Unit* unit = internal::UnitStack::GetUnit(unit_id, result);
    if (!unit)
        return;

    ImGuiIO& io = ImGui::GetIO();

    if (display_width == 0)
        display_width = io.DisplaySize.x;
    if (display_height == 0)
        display_height = io.DisplaySize.y;

    for (const auto& child : unit->item_tree)
    {
        child->API_Update(internal::bt::Vector2(0, 0),
                          internal::bt::Vector2(display_width, display_height));
    }
}

bool IsPressed(size_t unit_id, const char* item_id, bool* result)
{
    internal::ItemAPI* item = internal::UnitStack::GetItemAPI(unit_id, item_id,
                                                              result);
    if (!item)
        return false;

    return item->API_IsPressed();
}

bool IsHovered(size_t unit_id, const char* item_id, bool* result)
{
    internal::ItemAPI* item = internal::UnitStack::GetItemAPI(unit_id, item_id,
                                                              result);
    if (!item)
        return false;

    return item->API_IsHovered();
}

}  // namespace igm
