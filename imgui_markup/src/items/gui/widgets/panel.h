#ifndef IMGUI_MARKUP_SRC_ITEMS_GUI_WIDGETS_PANEL_H_
#define IMGUI_MARKUP_SRC_ITEMS_GUI_WIDGETS_PANEL_H_

/**
 * @file panel.h
 * @author FluxxCode (info.fluxxcode@gmail.com)
 * @brief Contains item 'Panel'
 * @copyright Copyright (c) 2022
 */

#include "items/gui/widgets/widget_base.h"

#include "imgui.h"  // ImGuiMouseButton

#include <string>  // std::string

namespace igm::internal
{

class Panel : public WidgetBase
{
public:
    Panel(std::string id, ItemBase* parent);

    void Update(bt::Vector2 position, bt::Vector2 available_size,
                bool dynamic_w, bool dynamic_h) noexcept;

private:
    StringWrapper title_;
    Vector2Wrapper position_;
    Vector2Wrapper size_;

    void Init();

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

    // Overwrite of WidgetBase
    bool OnProcessStart(std::string& error_message) noexcept { return true; }

    // See item_base.h for more information
    bool OnProcessEnd(std::string& error_message) noexcept;
};

}  // namespace igm::internal

#endif  // IMGUI_MARKUP_SRC_ITEMS_GUI_WIDGETS_PANEL_H_
