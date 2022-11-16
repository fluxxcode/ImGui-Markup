#include "impch.h"
#include "items/other/panel.h"

#include "imgui_fork.h"

/**
 * @file panel.cpp
 * @author FluxxCode (info.fluxxcode@gmail.com)
 * @brief Implementation of panel.h
 * @copyright Copyright (c) 2022
 */

namespace igm::internal
{

/**
 * TODO/IDEA:
 *   Maybe add clipping for the panels based on the root item of the
 *   current unit.
*/

Panel::Panel(std::string id, ItemBase* parent)
    : OtherBase(ItemType::kPanel, id, parent)
{
    this->InitAttribute("title", this->title_);
    this->InitAttribute("position", this->position_overwrite_);
    this->InitAttribute("size", this->size_overwrite_);
}

void Panel::ItemUpdate(bt::Vector2 position, bt::Vector2 available_size,
                       bool dynamic_w, bool dynamic_h) noexcept
{
    if (!this->initialized_)
        this->Init();

    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));

    ImGui::Begin(this->title_.GetString().c_str());

    ImGui::PopStyleVar();

    bt::Vector2 child_size = bt::Vector2(0, 0);

    // Set the child sizes to the same as the panel size, if the
    // panel size is overwritten from the markup language or
    // the first frame finished and the initial panel size is set.
    if (this->size_overwrite_.Value().x.IsValueSet() || this->initialized_)
        child_size.x = this->GetSize().x;
    if (this->size_overwrite_.Value().y.Value() || this->initialized_)
        child_size.y = this->GetSize().y - this->CalcTitlebarHeight();

    bt::Vector2 actual_size = bt::Vector2(0, this->CalcTitlebarHeight());
    for (const auto& child : this->child_items_)
    {
        // If child_size.x/y = 0 -> Enable dynamic size
        child->Update(bt::Vector2(0, this->CalcTitlebarHeight()), child_size,
                      child_size.x ? false : true, child_size.y ? false : true);

        // Only get the actual panel size after the first frame.
        // Resizing child items after the first frame will not have
        // affect on the panel's size.
        if (this->initialized_)
            continue;

        const bt::Vector2 child_size = child->GetSize();
        const bt::Vector2 child_pos = child->GetPosition();
        const bt::Vector2 size_overwrite_value = this->size_overwrite_.Value();

        if (!size_overwrite_value.x.IsValueSet())
        {
            if (child_pos.x + child_size.x > actual_size.x)
                actual_size.x = child_pos.x + child_size.x;
        }
        if (!size_overwrite_value.y.IsValueSet())
        {
            if (child_pos.y + child_size.y > actual_size.y)
                actual_size.y = child_pos.y + child_size.y;
        }
    }

    // Update the windows size to the max size of the child items.
    // This is necessary to include the actual size of the child items,
    // including padding, margin, etc..
    // ImGui only considers the item's draw size, which is not equal to the
    // item's actual size.
    if (!this->initialized_)
    {
        // Only update the windows size if the size overwrite is not set
        if (this->size_overwrite_.Value().x.IsValueSet())
            actual_size.x = this->size_overwrite_.Value().x;
        if (this->size_overwrite_.Value().y.IsValueSet())
            actual_size.y = this->size_overwrite_.Value().y;

        ImGui::SetWindowSize(actual_size);
    }

    this->position_ = ImGui::GetWindowPos();
    this->size_ = ImGui::GetWindowSize();
    this->is_hovered_ = ImGui::IsWindowHovered();

    ImGui::End();

    this->initialized_ = true;
}

void Panel::Init() const noexcept
{
    if (this->position_overwrite_.IsValueSet())
        ImGui::SetNextWindowPos(this->position_overwrite_);
    if (this->size_overwrite_.IsValueSet())
        ImGui::SetNextWindowSize(this->size_overwrite_);
}

bt::Vector2 Panel::GetPosition() const noexcept
{
    return this->position_;
}

bt::Vector2 Panel::GetSize() const noexcept
{
    if (!this->initialized_)
        return this->CalcItemSize();

    return this->size_;
}

bt::Vector2 Panel::CalcItemSize() const noexcept
{
    bt::Vector2 size = this->size_overwrite_;

    if (!size.x)
    {
        // Calc size.x based on child items
        for (const auto& child : this->child_items_)
        {
            if (child->GetSize().x > size.x)
                size.x = child->GetSize().x;
        }
    }

    if (!size.y)
    {
        // Calc size.y based on child items
        for (const auto& child : this->child_items_)
        {
            if (child->GetSize().y > size.y)
                size.y = child->GetSize().y;
        }
    }

    return size;
}

float Panel::CalcTitlebarHeight() const noexcept
{
    // Code when Panel flags are implemented
    // if (!this->is_title_bar_enabled)
    //    return 0;

    ImGuiStyle& style = ImGui::GetStyle();

    return ImGui::GetFontSize() + style.FramePadding.y * 2.0f;
}

bool Panel::API_IsItemPressed(ImGuiMouseButton mb) noexcept
{
    return this->is_hovered_ && ImGui::IsMouseClicked(mb);
}

bool Panel::API_IsItemHovered() noexcept
{
    return this->is_hovered_;
}

bool Panel::OnProcessEnd(std::string& error_message) noexcept
{
    this->title_.SetValue(this->title_.GetString() += "##" + this->unique_id_);
    return true;
}

}  // namespace igm::internal
