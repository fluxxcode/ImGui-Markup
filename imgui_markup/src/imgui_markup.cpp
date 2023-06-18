#include "impch.h"
#include "imgui_markup.h"

/**
 * @file imgui_markup.cpp
 * @author FluxxCode (info.fluxxcode@gmail.com)
 * @brief Implementation of imgui_markup.h
 * @copyright Copyright (c) 2022
 */

#include "common/unit_stack.h"
#include "common/units/unit_types.h"
#include "parser/parser.h"
#include "parser/parser_result.h"
#include "attribute_types/base_types/vector2.h"
#include "utility/utility.h"
#include "items/item_base.h"

#include "imgui.h"  // ImGuiMouseButton

#include <cassert>

namespace igm
{

size_t ParseFromFile(UnitType type, const char* path, bool* result_out)
{
    if (result_out)
        *result_out = false;

    internal::UnitBase* unit = nullptr;
    switch (type)
    {
    case UnitType::kGUI:
        unit = &internal::UnitStack::CreateEmptyUnit(internal::UnitType::kGUI);
        break;
    case UnitType::kTheme:
        unit = &internal::UnitStack::CreateEmptyUnit(
            internal::UnitType::kTheme);
        break;
    default:
        assert("Undefined unit type");
    }
    if (!unit)
        assert("Unit is nullptr");

    internal::Parser parser(*unit);

    const internal::ParserResult result = parser.ParseFromFile(path);
    if (result.type != internal::ParserResultType::kSuccess)
    {
        internal::UnitStack::SetLastResult(unit->GetID(),
            Result(ResultType::kParserError, result.ToString()));

        return unit->GetID();
    }

    if (result_out)
        *result_out = true;

    return unit->GetID();
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
    internal::UnitBase* unit = internal::UnitStack::GetUnit(unit_id, result);
    if (!unit)
        return;

    unit->Update(display_width, display_height);
}

void Update(size_t unit, bool* result)
{
    ImGuiIO& io = ImGui::GetIO();

    const float display_width = io.DisplaySize.x;
    const float display_height = io.DisplaySize.y;

    Update(unit, display_width, display_height, result);
}

std::vector<const char*> GetLoadedThemes(size_t unit_id, bool* result)
{
    internal::UnitBase* unit = internal::UnitStack::GetUnit(unit_id, result);
    if (!unit)
        return {};

    if (unit->GetType() != internal::UnitType::kTheme)
        // TODO: Add error message
        return {};

    internal::ThemeUnit* theme_unit = dynamic_cast<internal::ThemeUnit*>(unit);
    return theme_unit->GetLoadedThemes();
}

bool InitUnitTheme(size_t dst_unit, size_t src_unit, const char* theme_id,
                   bool* result)
{
    // TODO: Improve error handling
    internal::UnitBase* unit = internal::UnitStack::GetUnit(dst_unit, result);
    if (!unit)
        return false;

    if (unit->GetType() != internal::UnitType::kGUI)
        // TODO: Add error message
        return false;
    internal::GUIUnit* gui_unit = (internal::GUIUnit*)unit;

    internal::ItemAPI* item = internal::UnitStack::GetItemAPI(src_unit,
                                                              theme_id, result);
    if (!item)
        return false;

    internal::ItemBase* item_base = (internal::ItemBase*)(item);

    if (item_base->GetType() != internal::ItemType::kTheme)
        // TODO: Add error message
        return false;

    gui_unit->ApplyTheme(*(internal::Theme*)item_base);

    return true;
}

bool IsItemPressed(size_t unit_id, const char* item_id, MouseButton mb,
               bool* result) noexcept
{
    internal::ItemAPI* item = internal::UnitStack::GetItemAPI(unit_id, item_id,
                                                              result);
    if (!item)
        return false;

    return item->API_IsItemPressed(internal::utils::ConvertMouseButton(mb));
}

bool IsItemHovered(size_t unit_id, const char* item_id, bool* result) noexcept
{
    internal::ItemAPI* item = internal::UnitStack::GetItemAPI(unit_id, item_id,
                                                              result);
    if (!item)
        return false;

    return item->API_IsItemHovered();
}

bool IsCheckboxChecked(size_t unit_id, const char* item_id,
                       bool* result) noexcept
{
    internal::ItemAPI* item = internal::UnitStack::GetItemAPI(unit_id, item_id,
                                                              result);
    if (!item)
        return false;

    return item->API_IsCheckboxChecked();
}

}  // namespace igm
