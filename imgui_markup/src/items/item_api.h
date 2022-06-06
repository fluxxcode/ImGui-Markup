#ifndef IMGUI_MARKUP_SRC_ITEMS_ITEM_API_H_
#define IMGUI_MARKUP_SRC_ITEMS_ITEM_API_H_

/**
 * @file item_api.h
 * @author FluxxCode (info.fluxxcode@gmail.com)
 * @brief Contains the main item API class.
 * @copyright Copyright (c) 2022
 */

#include "attribute_types/base_types/vector2.h"

#include "imgui.h"  // ImGuiMouseButton

namespace igm::internal
{

/**
 * Parent of every item within the markup language,
 * containing API functions and their default return values.
 */
struct ItemAPI
{
    virtual void API_Update(bt::Vector2 position,
                            bt::Vector2 size) noexcept = 0;

    virtual bool API_IsItemPressed(ImGuiMouseButton btn) noexcept { return false; }
    virtual bool API_IsItemHovered() noexcept { return false; }

    virtual bool API_IsCheckboxChecked() noexcept { return false;}
};

}  // namespace igm::internal

#endif  // IMGUI_MARKUP_SRC_ITEMS_ITEM_API_H_
