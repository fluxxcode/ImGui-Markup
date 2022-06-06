#ifndef IMGUI_MARKUP_SRC_ITEMS_WIDGETS_TEXT_H_
#define IMGUI_MARKUP_SRC_ITEMS_WIDGETS_TEXT_H_

/**
 * @file text.h
 * @author FluxxCode (info.fluxxcode@gmail.com)
 * @brief Contains item 'Text'
 * @copyright Copyright (c) 2022
 */

#include "items/widgets/widget_base.h"

#include "imgui.h"  // ImGuiMouseButton

#include <string>  // std::string

namespace igm::internal
{

class Text : public WidgetBase
{
public:
    Text(std::string id, ItemBase* parent);

    void WidgetUpdate(bt::Vector2 position, bt::Vector2 size) noexcept;

private:
    StringWrapper text_;

    bool is_hovered_ = false;

    // API functions
    bool API_IsPressed(ImGuiMouseButton btn) noexcept;
    bool API_IsHovered() noexcept;
};

}  // namespace igm::internal

#endif  // IMGUI_MARKUP_SRC_ITEMS_WIDGETS_TEXT_H_
