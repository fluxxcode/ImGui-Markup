#ifndef IMGUI_MARKUP_SRC_ITEM_WIDGETS_PANEL_H_
#define IMGUI_MARKUP_SRC_ITEM_WIDGETS_PANEL_H_

/**
 * @file panel.h
 * @author FluxxCode (info.fluxxcode@gmail.com)
 * @brief Contains item 'Panel'
 * @copyright Copyright (c) 2022
 */

#include "items/widgets/widget_base.h"

#include <string>  // std::string

namespace igm::internal
{

struct Panel : public WidgetBase
{
    Panel(std::string id, ItemBase* parent);

    void Update(bt::Vector2 position, bt::Vector2 size) noexcept;
};

}  // namespace igm::internal

#endif  // IMGUI_MARKUP_SRC_ITEM_WIDGETS_PANEL_H_
