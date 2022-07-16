#include "impch.h"
#include "items/widgets/widget_base.h"

/**
 * @file widget_base.cpp
 * @author FluxxCode (info.fluxxcode@gmail.com)
 * @brief Implementation of widget_base.h
 * @copyright Copyright (c) 2022
 */

#include "imgui_internal.h"

namespace igm::internal
{

WidgetBase::WidgetBase(ItemType type, std::string id, ItemBase* parent)
    : ItemBase(type, ItemCategory::kWidget, id, parent)
{
    this->InitAttribute("position", this->position_overwrite_);
    this->InitAttribute("size", this->size_overwrite_);
    this->InitAttribute("margin", this->margin_);
}

bt::Vector2 WidgetBase::GetSize() const noexcept
{
    if (!this->IsInitialized())
        return CalcSize();

    return this->size_;
}

bt::Vector2 WidgetBase::GetPosition() const noexcept
{
    return this->position_;
}

void WidgetBase::Update(bt::Vector2 position, bt::Vector2 available_size,
                        bool dynamic_w, bool dynamic_h) noexcept
{
    this->BeginPosition(position);
    this->BeginSize(available_size, dynamic_w, dynamic_h);

    if (this->visible_)
    {
        // TODO: Update so the clipping area will be created even when
        //       only one value is dynamic
        if (!dynamic_w && !dynamic_h)
            this->BeginClippingArea();

        ImGui::PushID(this);
        ImGui::SetCursorPos(this->item_draw_position_);
        this->WidgetUpdate(this->item_draw_position_, this->item_draw_size_);
        ImGui::PopID();

        if (!dynamic_w && !dynamic_h)
            this->EndClippingArea();
    }

    this->EndSize(dynamic_w, dynamic_h);
}

void WidgetBase::BeginPosition(bt::Vector2 position_in) noexcept
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

void WidgetBase::BeginSize(bt::Vector2 available_size, bool& dynamic_w,
                           bool& dynamic_h) noexcept
{
    const bt::Margin& margin = this->margin_.ValueReference();

    if (this->size_overwrite_.ValueReference().x.IsValueSet())
        dynamic_w = false;
    if (this->size_overwrite_.ValueReference().y.IsValueSet())
        dynamic_h = false;

    if (dynamic_w)
        item_draw_size_.x = 0;
    if (dynamic_h)
        item_draw_size_.y = 0;

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

    if (this->size_overwrite_.IsValueSet())
    {
        this->item_draw_size_ = this->size_overwrite_;
        this->size_.x = size_overwrite_.Value().x + margin.left + margin.right;
        this->size_.y = size_overwrite_.Value().y + margin.top + margin.bottom;
    }

    if ((this->item_draw_size_.x <= 0 && dynamic_w == false) ||
        (this->item_draw_size_.y <= 0 && dynamic_h == false))
    {
        this->visible_ = false;
    }
}

void WidgetBase::EndSize(bool dynamic_w, bool dynamic_h) noexcept
{
    const bt::Margin& margin = this->margin_.ValueReference();
    const bt::Vector2 actual_size = this->GetActualSize();

    if (dynamic_w)
        this->size_.x = actual_size.x + margin.left + margin.right;
    if (dynamic_h)
        this->size_.y = actual_size.y + margin.top + margin.bottom;
}

void WidgetBase::BeginClippingArea() const noexcept
{
    const ImGuiWindow* window = ImGui::GetCurrentWindow();

    ImVec2 min = ImVec2(this->item_draw_position_.x + window->Pos.x,
                        this->item_draw_position_.y + window->Pos.y);
    ImVec2 max = ImVec2(min.x + this->item_draw_size_.x,
                        min.y + this->item_draw_size_.y);

    ImGui::PushClipRect(min, max, true);

    // NOTE: Only used for debugging
    // ImDrawList* draw_list = ImGui::GetWindowDrawList();
    // draw_list->AddRectFilled(min, max, this->clipping_area_color_);
}

void WidgetBase::EndClippingArea() const noexcept
{
    ImGui::PopClipRect();
}

bt::Vector2 WidgetBase::CalcSize() const noexcept
{
    // TODO: Implement cache

    const bt::Vector2 size = this->CalcItemSize();
    const bt::Margin margin = this->margin_.Value();

    return bt::Vector2(size.x + margin.left + margin.right,
                       size.y + margin.top + margin.bottom);
}

void WidgetBase::API_Update(bt::Vector2 position, bt::Vector2 size) noexcept
{
    this->Update(position, size, false, false);
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
