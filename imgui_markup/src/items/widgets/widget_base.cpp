#include "impch.h"
#include "items/widgets/widget_base.h"

#include "imgui_fork.h"

/**
 * @file widget_base.cpp
 * @author FluxxCode (info.fluxxcode@gmail.com)
 * @brief Implementation of widget_base.h
 * @copyright Copyright (c) 2022
 */

namespace igm::internal
{

WidgetBase::WidgetBase(ItemType type, std::string id, ItemBase* parent,
                       bool create_clipping_area_)
    : ItemBase(type, ItemCategory::kWidget, id, parent),
      create_clipping_area_(create_clipping_area_)
{
    this->InitAttribute("position", this->position_overwrite_);
    this->InitAttribute("size", this->size_overwrite_);
    this->InitAttribute("margin", this->margin_);
}

void WidgetBase::Update(bt::Vector2 position, bt::Vector2 size) noexcept
{
    this->PreparePositionAndSize(position, size);

    ImGui::PushID(this);

    ImGui::SetCursorPos(position);

    if (this->create_clipping_area_)
        this->BeginClippingArea();

    this->WidgetUpdate(position, size);

    if (this->create_clipping_area_)
        this->EndClippingArea();

    ImGui::PopID();

    this->UpdatePositionAndSize(position, size);
}

bt::Vector2 WidgetBase::GetSize() const noexcept
{
    if (!this->initialized_)
    {
        if (this->calculated_size_)
            return this->calculated_size_cache_;

        this->calculated_size_cache_ = this->CalcFullSize();
        this->calculated_size_ = true;

        return this->calculated_size_cache_;
    }

    return this->size_;
}

void WidgetBase::API_Update(bt::Vector2 position, bt::Vector2 size) noexcept
{
    this->Update(position, size);
}

void WidgetBase::PreparePositionAndSize(bt::Vector2& position,
                                        bt::Vector2& size) const noexcept
{
    const bt::Margin margin = this->margin_.GetValue();

    if (this->position_overwrite_.IsValueSet())
        position = this->position_overwrite_.GetValue();
    if (this->size_overwrite_.IsValueSet())
        size = this->size_overwrite_.GetValue();

    position.x += margin.left;
    position.y += margin.top;

    // Remove margin from the size that will be parsed to the actual item
    if (size.x != 0)
        size.x -= margin.left - margin.right;
    if (size.y != 0)
        size.y -= margin.top - margin.bottom;
}

void WidgetBase::UpdatePositionAndSize(const bt::Vector2& prepared_position,
                                       const bt::Vector2& prepared_size)
                                       noexcept
{
    const bt::Margin& margin = this->margin_.GetValueReference();

    // Position
    this->position_ = prepared_position;
    this->position_.x -= margin.left;
    this->position_.y -= margin.top;

    // Size
    this->size_ = prepared_size;

    const bt::Vector2 actual_size = this->GetActualSize();

    if (this->size_.x == 0)
        this->size_.x = actual_size.x;
    if (this->size_.y == 0)
        this->size_.y = actual_size.y;

    this->size_.x += margin.left + margin.right;
    this->size_.y += margin.top + margin.bottom;
}

void WidgetBase::BeginClippingArea()
    noexcept
{
    // TODO: Implementation
}

void WidgetBase::EndClippingArea() const noexcept
{
    // TODO: Implementation
}

bt::Vector2 WidgetBase::CalcFullSize() const noexcept
{
    bt::Vector2 item_size = this->CalcItemSize();

    item_size.x += this->margin_.GetValue().left +
                   this->margin_.GetValue().right;

    item_size.y += this->margin_.GetValue().top +
                   this->margin_.GetValue().bottom;

    return item_size;
}

bool WidgetBase::OnProcessStart(std::string& error_message) noexcept
{
    const ItemBase* parent = this->parent_;
    while (parent)
    {
        if (parent->GetType() == ItemType::kPanel)
            return true;

        parent = parent->GetParent();
    }

    error_message = "One of the items parent item must be an item "
                    "of type Panel";

    return false;
}

}  // namespace igm::internal
