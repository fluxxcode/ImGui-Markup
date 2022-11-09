#include "impch.h"
#include "items/gui/gui_base.h"

/**
 * @file gui_base.cpp
 * @author FluxxCode (info.fluxxcode@gmail.com)
 * @brief Implementation of gui_base.h
 * @copyright Copyright (c) 2022
 */

#include "imgui_internal.h"

namespace igm::internal
{

GUIBase::GUIBase(ItemType type, ItemCategory category, std::string id,
                 ItemBase* parent, bool clipping_area)
    : ItemBase(type, category, id, parent),
      clipping_area_(clipping_area)
{
    this->InitAttribute("position", this->position_overwrite_);
    this->InitAttribute("size", this->size_overwrite_);
    this->InitAttribute("margin", this->margin_);
}

void GUIBase::Update(bt::Vector2 position, bt::Vector2 available_size,
                     bool dynamic_w, bool dynamic_h) noexcept
{
    this->BeginPosition(position);
    this->BeginSize(available_size, dynamic_w, dynamic_h);

    if (this->visible_)
    {
        // Don't create a clipping area if both width and height size is dynamic
        if ((!dynamic_w || !dynamic_h) && this->clipping_area_)
            this->BeginClippingArea(dynamic_w, dynamic_h);

        this->GUIUpdate(this->item_draw_position_, this->item_draw_size_);

        if ((!dynamic_w || !dynamic_h) && this->clipping_area_)
            this->EndClippingArea();
    }

    this->EndSize(dynamic_w, dynamic_h);
}

void GUIBase::BeginPosition(bt::Vector2 position_in) noexcept
{
    this->position_ = position_in;
    if (this->position_overwrite_.IsValueSet())
        this->position_ = this->position_overwrite_;

    const bt::Margin& margin = this->margin_.ValueReference();

    bt::Vector2 draw_position = this->position_;
    draw_position.x += margin.left;
    draw_position.y += margin.top;

    this->item_draw_position_ = draw_position;
}

void GUIBase::BeginSize(bt::Vector2 available_size, bool& dynamic_w,
                           bool& dynamic_h) noexcept
{
    const bt::Margin& margin = this->margin_.ValueReference();

    // Check if the size overwrite is set and if so, overwrite the
    // dynamic status which is set from the parent item.
    if (this->size_overwrite_.ValueReference().x.IsValueSet())
        dynamic_w = false;
    if (this->size_overwrite_.ValueReference().y.IsValueSet())
        dynamic_h = false;

    // Set the ImGui Item size to 0, since this is the way of telling ImGui
    // that the item does't have a fixed size.
    if (dynamic_w)
        item_draw_size_.x = 0;
    if (dynamic_h)
        item_draw_size_.y = 0;

    // Set the size for the case, that its dynamic and not overwritten from
    // the markup language.
    if (!dynamic_w)
    {
        this->size_.x = available_size.x;
        this->item_draw_size_.x = available_size.x - margin.left - margin.right;
    }
    if (!dynamic_h)
    {
        this->size_.y = available_size.y;
        this->item_draw_size_.y = available_size.y - margin.top - margin.bottom;
    }

    // Overwrite the size again if its overwritten via the markup language.
    if (this->size_overwrite_.IsValueSet())
    {
        this->item_draw_size_ = this->size_overwrite_;
        this->size_.x = size_overwrite_.Value().x + margin.left + margin.right;
        this->size_.y = size_overwrite_.Value().y + margin.top + margin.bottom;
    }

    // Check if the item is visible
    if ((this->item_draw_size_.x <= 0 && dynamic_w == false) ||
        (this->item_draw_size_.y <= 0 && dynamic_h == false))
    {
        this->visible_ = false;
    }
}

void GUIBase::EndSize(bool dynamic_w, bool dynamic_h) noexcept
{
    const bt::Margin& margin = this->margin_.ValueReference();
    const bt::Vector2 actual_size = this->GetActualSize();

    // Update the item's size if its dynamic, using the actual size which
    // is set by the inheriting item.
    if (dynamic_w)
        this->size_.x = actual_size.x + margin.left + margin.right;
    if (dynamic_h)
        this->size_.y = actual_size.y + margin.top + margin.bottom;
}

void GUIBase::BeginClippingArea(bool dynamic_w, bool dynamic_h) noexcept
{
    const ImGuiWindow* window = ImGui::GetCurrentWindow();

    ImVec2 min = ImVec2(this->item_draw_position_.x + window->Pos.x,
                        this->item_draw_position_.y + window->Pos.y);
    ImVec2 max = ImVec2(min.x + this->item_draw_size_.x,
                        min.y + this->item_draw_size_.y);

    const bt::Margin& margin = this->margin_.ValueReference();

    // Making sure the clipping area is big enough if one of the sizes
    // is dynamic. Otherwise the clipping area width or height
    // would be 0.

    /**
     * Offset to make sure the clipping are is big enough when
     * calculating and estimating the size at the first frame.
     */
    static const float offset = 20.0f;

    if (dynamic_w)
        max.x = min.x + this->GetSize().x + offset - margin.left - margin.right;
    if (dynamic_h)
        max.y = min.y + this->GetSize().y + offset - margin.top - margin.bottom;

    ImGui::PushClipRect(min, max, true);

    // NOTE: Only used for debugging
    // ImDrawList* draw_list = ImGui::GetWindowDrawList();
    // draw_list->AddRectFilled(min, max, this->clipping_area_color_);
}

void GUIBase::EndClippingArea() const noexcept
{
    ImGui::PopClipRect();
}

bt::Vector2 GUIBase::CalcSize() const noexcept
{
    // TODO: Implement cache

    const bt::Vector2 size = this->CalcItemSize();
    const bt::Margin margin = this->margin_.Value();

    return bt::Vector2(size.x + margin.left + margin.right,
                       size.y + margin.top + margin.bottom);
}

void GUIBase::API_Update(bt::Vector2 position, bt::Vector2 size) noexcept
{
    this->Update(position, size, false, false);
}

}  // namespace igm::internal
