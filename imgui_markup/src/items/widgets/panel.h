#ifndef IMGUI_MARKUP_SRC_ITEMS_WIDGETS_PANEL_H_
#define IMGUI_MARKUP_SRC_ITEMS_WIDGETS_PANEL_H_

/**
 * @file panel.h
 * @author FluxxCode (info.fluxxcode@gmail.com)
 * @brief Contains item 'Panel'
 * @copyright Copyright (c) 2022
 */

#include "items/widgets/widget_base.h"

#include "imgui.h"  // ImGuiMouseButton

#include <string>  // std::string

namespace igm::internal
{

class Panel : public WidgetBase
{
public:
    Panel(std::string id, ItemBase* parent);

    void Update(bt::Vector2 position, bt::Vector2 size) noexcept;

private:
    StringWrapper title_;
    Vector2Wrapper position_;
    Vector2Wrapper size_;

    bool init_ = false;

    bool is_hovered_ = false;

    void Init();

    // API functions
    bool API_IsPressed(ImGuiMouseButton btn) noexcept;
    bool API_IsHovered() noexcept;

    // Overwrite of WidgetBase
    bool OnProcessStart(std::string& error_message) noexcept { return true; }

    // See item_base.h for more information
    bool OnProcessEnd(std::string& error_message) noexcept;
};

}  // namespace igm::internal

#endif  // IMGUI_MARKUP_SRC_ITEMS_WIDGETS_PANEL_H_
