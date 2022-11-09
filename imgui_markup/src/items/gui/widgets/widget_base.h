#ifndef IMGUI_MARKUP_SRC_ITEMS_GUI_WIDGETS_WIDGET_BASE_H_
#define IMGUI_MARKUP_SRC_ITEMS_GUI_WIDGETS_WIDGET_BASE_H_

/**
 * @file widget_base.h
 * @author FluxxCode (info.fluxxcode@gmail.com)
 * @brief Contains base for every widget item within the markup language.
 * @copyright Copyright (c) 2022
 */

#include "items/gui/gui_base.h"

namespace igm::internal
{

class WidgetBase : public GUIBase
{
public:
    WidgetBase(ItemType type, std::string id, ItemBase* parent,
               bool clipping_area = true);
    WidgetBase(const WidgetBase&) = delete;

private:

    /**
     * Main update function that should be implemented by the
     * inheriting item.
     * When implemented, the ImGui ID, margin, size and position overrides
     * are already handled and don't have to be managed by the
     * inheriting item.
     */
    virtual void WidgetUpdate(bt::Vector2 position,
                              bt::Vector2 size) noexcept { }

    // See gui_base.h for more information
    void GUIUpdate(bt::Vector2 position, bt::Vector2 size) noexcept;
};

}  // namespace igm::internal

#endif  // IMGUI_MARKUP_SRC_ITEMS_GUI_WIDGETS_WIDGET_BASE_H_
