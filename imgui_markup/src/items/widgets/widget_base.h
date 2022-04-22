#ifndef IMGUI_MARKUP_SRC_ITEMS_WIDGETS_WIDGET_BASE_H_
#define IMGUI_MARKUP_SRC_ITEMS_WIDGETS_WIDGET_BASE_H_

/**
 * @file widget_base.h
 * @author FluxxCode (info.fluxxcode@gmail.com)
 * @brief Contains base for every widget item within the markup language.
 * @copyright Copyright (c) 2022
 */

#include "items/item_base.h"

namespace igm::internal
{

class WidgetBase : public ItemBase
{
public:
    WidgetBase(ItemType type, std::string id, ItemBase* parent)
        : ItemBase(type, ItemCategory::kWidget, id, parent)
    { }

    WidgetBase(const WidgetBase&) = delete;

private:
    // TODO: pos, size, default functions like IsPressed, IsHovered, etc.
};

}  // namespace igm::internal

#endif  // IMGUI_MARKUP_SRC_ITEMS_WIDGETS_WIDGET_BASE_H_
