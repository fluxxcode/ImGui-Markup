#ifndef IMGUI_MARKUP_SRC_ITEMS_GUI_VIEWS_VIEW_BASE_H_
#define IMGUI_MARKUP_SRC_ITEMS_GUI_VIEWS_VIEW_BASE_H_

/**
 * @file view_base.h
 * @author FluxxCode (info.fluxxcode@gmail.com)
 * @brief Contains base for every view.
 * @copyright Copyright (c) 2022
 */

#include "items/item_base.h"

namespace igm::internal
{

struct ViewBase : public ItemBase
{
    ViewBase(ItemType type, std::string id, ItemBase* parent)
        : ItemBase(type, ItemCategory::kView, id, parent)
    { }

    ViewBase(const ViewBase&) = delete;

    virtual void API_Update(bt::Vector2 position, bt::Vector2 size) noexcept;
};

}  // namespace igm::internal

#endif  // IMGUI_MARKUP_SRC_ITEMS_GUI_VIEWS_VIEW_BASE_H_
