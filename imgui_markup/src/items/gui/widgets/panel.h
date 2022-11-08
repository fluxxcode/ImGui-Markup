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

/**
 * The Panel does not inherit from WidgetBase since it does quite a lot of
 * things differently.
 */
class Panel : public ItemBase
{
public:
    Panel(std::string id, ItemBase* parent);

    void Update(bt::Vector2 position, bt::Vector2 available_size,
                bool dynamic_w, bool dynamic_h) noexcept;

private:
    bt::Vector2 position_;
    bt::Vector2 size_;

    Vector2Wrapper position_overwrite_;
    Vector2Wrapper size_overwrite_;
    StringWrapper title_;

    // See widget_base.h for more information
    bool is_hovered_ = false;
    bool initialized_ = false;

    void Init() const noexcept;

    bt::Vector2 GetSize() const noexcept;
    bt::Vector2 GetPosition() const noexcept;

    bt::Vector2 CalcItemSize() const noexcept;

    float CalcTitlebarHeight() const noexcept;

    // API functions
    void API_Update(bt::Vector2 position, bt::Vector2 size) noexcept;

    bool API_IsItemPressed(ImGuiMouseButton btn) noexcept;
    bool API_IsItemHovered() noexcept;

    // See item_base.h for more information
    virtual bool OnProcessEnd(std::string& error_message) noexcept;
};

}  // namespace igm::internal

#endif  // IMGUI_MARKUP_SRC_ITEMS_GUI_WIDGETS_PANEL_H_
