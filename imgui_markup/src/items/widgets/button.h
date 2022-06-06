#ifndef IMGUI_MARKUP_SRC_ITEMS_WIDGETS_BUTTON_H_
#define IMGUI_MARKUP_SRC_ITEMS_WIDGETS_BUTTON_H_

/**
 * @file button.h
 * @author FluxxCode (info.fluxxcode@gmail.com)
 * @brief Contains item 'Button'
 * @copyright Copyright (c) 2022
 */

#include "items/widgets/widget_base.h"

#include "imgui.h"  // ImGuiMouseButton

#include <string>  // std::string

namespace igm::internal
{

class Button : public WidgetBase
{
public:
    Button(std::string id, ItemBase* parent);

    void Update(bt::Vector2 position, bt::Vector2 size) noexcept;

private:
    StringWrapper text_;
    Vector2Wrapper size_;

    bool is_hovered_ = false;

    void Init();

    // API functions
    bool API_IsPressed(ImGuiMouseButton btn) noexcept;
    bool API_IsHovered() noexcept;

    // See item_base.h for more information
    bool OnProcessStart(std::string& error_message);
};

}  // namespace igm::internal

#endif  // IMGUI_MARKUP_SRC_ITEMS_WIDGETS_BUTTON_H_