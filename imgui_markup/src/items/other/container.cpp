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
    this->position_ = position;
    this->size_ = bt::Vector2(0.0f, 0.0f);

    for (const auto& child : this->child_items_)
    {
        child->Update(position, available_size, dynamic_w, dynamic_h);

        const bt::Vector2 child_size = child->GetSize();
        const bt::Vector2 child_pos = child->GetPosition();

        if (child_pos.x + child_size.x > this->size_.x)
            this->size_.x = child_pos.x + child_size.x;
        if (child_pos.y + child_size.y > this->size_.y)
            this->size_.y = child_pos.y + child_size.y;
    }
}

}  // namespace igm::internal
