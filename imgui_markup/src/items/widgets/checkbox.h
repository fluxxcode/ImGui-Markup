#ifndef IMGUI_MARKUP_SRC_ITEMS_WIDGETS_CHECKBOX_H_
#define IMGUI_MARKUP_SRC_ITEMS_WIDGETS_CHECKBOX_H_

/**
 * @file checkbox.h
 * @author FluxxCode (info.fluxxcode@gmail.com)
 * @brief Contains item 'Checkbox'
 * @copyright Copyright (c) 2022
 */

#include "items/widgets/widget_base.h"

#include "imgui.h"  // ImGuiMouseButton

#include <string>  // std::string

namespace igm::internal
{

class Checkbox : public WidgetBase
{
public:
    Checkbox(std::string id, ItemBase* parent);

    void WidgetUpdate(bt::Vector2 position, bt::Vector2 size) noexcept;

private:
    StringWrapper text_;
    BoolWrapper is_checked_;

    bool is_hovered_ = false;

    // API functions
    bool API_IsItemPressed(ImGuiMouseButton btn) noexcept;
    bool API_IsItemHovered() noexcept;
    bool API_IsCheckboxChecked() noexcept;
};

}  // namespace igm::internal

#endif  // IMGUI_MARKUP_SRC_ITEMS_WIDGETS_CHECKBOX_H_
