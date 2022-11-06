#include "impch.h"
#include "items/root_item.h"

/**
 * @file root_item.cpp
 * @author FluxxCode (info.fluxxcode@gmail.com)
 * @brief Implementation of root_item.h
 * @copyright Copyright (c) 2022
 */

#include "imgui_internal.h"

namespace igm::internal
{

RootItem::RootItem()
{ }

void RootItem::Update(size_t display_width, size_t display_height) noexcept
{
    // TODO: Push root panel of the app GUI

    for (const auto& child : this->item_tree)
    {
        child->API_Update(internal::bt::Vector2(0, 0),
                          internal::bt::Vector2(display_width, display_height));
    }

    // TODO: Pop/End root panel of the app GUI
}

void RootItem::Clear() noexcept
{
    this->item_tree.clear();
}

}  // namespace igm::internal
