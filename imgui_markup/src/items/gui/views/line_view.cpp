#include "impch.h"
#include "items/gui/views/line_view.h"

/**
 * @file line_view.cpp
 * @author FluxxCode (info.fluxxcode@gmail.com)
 * @brief Implementation of im_line_view.h
 * @copyright Copyright (c) 2022 - 2023
 */

namespace igm::internal
{

LineView::LineView(std::string id, ItemBase* parent)
    : ViewBase(ItemType::kLineView, id, parent, true)
{
    this->InitAttribute("padding", this->padding_);
    this->InitAttribute("spacing", this->spacing_);
    this->InitAttribute("orientation", this->orientation_);
}

void LineView::ViewUpdate(bt::Vector2 position, bt::Vector2 size) noexcept
{
    const bt::Padding& padding = this->padding_.ValueReference();

    bt::Vector2 cursor_position = position;
    cursor_position.x += padding.left;
    cursor_position.y += padding.top;

    bt::Vector2 actual_size;

    for (const auto& child : this->child_items_)
    {
        child->Update(cursor_position, bt::Vector2(0.0f, 0.0f), true, true);

        // Skip items like container, panel etc.
        if (child->GetCategory() == ItemCategory::kOther)
            continue;

        const bt::Vector2 child_size = child->GetSize();
        const bt::Vector2 child_pos = child->GetPosition();

        if (child_pos.x + child_size.x - position.x > actual_size.x)
            actual_size.x = child_pos.x + child_size.x - position.x;
        if (child_pos.y + child_size.y - position.y > actual_size.y)
            actual_size.y = child_pos.y + child_size.y - position.y;

        if (this->orientation_ == bt::Orientation::kVertical)
            cursor_position.y = child_pos.y + child_size.y + this->spacing_;
        else if (this->orientation_ == bt::Orientation::kHorizontal)
            cursor_position.x = child_pos.x + child_size.x + this->spacing_;
    }

    actual_size.x += padding.right;
    actual_size.y += padding.bottom;

    this->actual_size_ = actual_size;
    this->initialized_ = true;
}

bt::Vector2 LineView::CalcItemSize() const noexcept
{
    // NOTE: This is currently quite inaccurate if the LinewView is not at
    //       the position (0, 0), since the position is not considered.

    bt::Vector2 size;
    for (const auto& child : this->child_items_)
    {
        const bt::Vector2 child_size = child->GetSize();
        const bt::Vector2 child_pos = child->GetPosition();

        if (child_pos.x + child_size.x > size.x)
            size.x = child_pos.x + child_size.x;
        if (child_pos.y + child_size.y > size.y)
            size.y = child_pos.y + child_size.y;
    }

    return size;
}

}  // namespace igm::internal
