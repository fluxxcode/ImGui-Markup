#ifndef IMGUI_MARKUP_SRC_ITEMS_GUI_WIDGETS_CHECKBOX_H_
#define IMGUI_MARKUP_SRC_ITEMS_GUI_WIDGETS_CHECKBOX_H_

/**
 * @file checkbox.h
 * @author FluxxCode (info.fluxxcode@gmail.com)
 * @brief Contains item 'Checkbox'
 * @copyright Copyright (c) 2022 - 2023
 */

#include "items/gui/widgets/widget_base.h"

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

    // See widget_base.h for more information
    bt::Vector2 actual_size_;
    bool is_hovered_ = false;
    bool initialized_ = false;

    bt::Vector2 CalcItemSize() const noexcept;
    inline bool IsInitialized() const noexcept
        { return this->initialized_; }
    inline bt::Vector2 GetActualSize() const noexcept
        { return this->actual_size_; }

    // API functions
    bool API_IsItemPressed(ImGuiMouseButton btn) noexcept;
    bool API_IsItemHovered() noexcept;
    bool API_IsCheckboxChecked() noexcept;
};

}  // namespace igm::internal

#endif  // IMGUI_MARKUP_SRC_ITEMS_GUI_WIDGETS_CHECKBOX_H_
