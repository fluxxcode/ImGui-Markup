#include "impch.h"
#include "items/other/container.h"

/**
 * @file container.cpp
 * @author FluxxCode (info.fluxxcode@gmail.com)
 * @brief Implementation of container.h
 * @copyright Copyright (c) 2022
 */

namespace igm::internal
{

Container::Container(std::string id, ItemBase* parent)
    : OtherBase(ItemType::kContainer, id, parent)
{ }

void Container::Update(bt::Vector2 position, bt::Vector2 available_size,
                       bool dynamic_w, bool dynamic_h) noexcept
{
    for (const auto& child : this->child_items_)
        child->Update(position, available_size, dynamic_w, dynamic_h);
}

}  // namespace igm::internal
