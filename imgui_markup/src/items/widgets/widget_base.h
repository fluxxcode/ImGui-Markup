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

    /**
     * Implementation of the ItemBase::Update function.
     * Already pushes an unique ID for the item and calls WidgetUpdate().
     * Can be overwritten to prevent it.
     */
    virtual void Update(bt::Vector2 position, bt::Vector2 size) noexcept;

    /**
     * Update function of the Item API, usually called for items
     * that are at the root of the item tree.
     * Currently only calls the Update function.
     */
    virtual void API_Update(bt::Vector2 position, bt::Vector2 size) noexcept;

protected:
    /**
     * Main update function that should be implemented by the
     * inheriting item.
     * If this function is implemented, the ImGui ID push/pop no longer has
     * to be done by the child items.
     */
    virtual void WidgetUpdate(bt::Vector2 position,
                              bt::Vector2 size) noexcept { }

private:
    // See item_base.h for more information
    virtual bool OnProcessStart(std::string& error_message) noexcept;
};

}  // namespace igm::internal

#endif  // IMGUI_MARKUP_SRC_ITEMS_WIDGETS_WIDGET_BASE_H_
