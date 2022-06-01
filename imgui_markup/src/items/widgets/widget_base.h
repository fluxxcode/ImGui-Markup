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

struct WidgetBase : public ItemBase
{
    WidgetBase(ItemType type, std::string id, ItemBase* parent)
        : ItemBase(type, ItemCategory::kWidget, id, parent)
    { }

    WidgetBase(const WidgetBase&) = delete;

    virtual void API_Update() noexcept { this->Update(); }
};

}  // namespace igm::internal

#endif  // IMGUI_MARKUP_SRC_ITEMS_WIDGETS_WIDGET_BASE_H_
