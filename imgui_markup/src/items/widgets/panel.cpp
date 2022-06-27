#include "impch.h"
#include "items/widgets/panel.h"

#include "imgui_fork.h"

/**
 * @file panel.cpp
 * @author FluxxCode (info.fluxxcode@gmail.com)
 * @brief Implementation of panel.h
 * @copyright Copyright (c) 2022
 */

namespace igm::internal
{

Panel::Panel(std::string id, ItemBase* parent)
    : WidgetBase(ItemType::kPanel, id, parent, false)
{
    this->InitAttribute("title", this->title_);
    this->InitAttribute("position", this->position_);
    this->InitAttribute("size", this->size_);
}

void Panel::Update(bt::Vector2 position, bt::Vector2 size) noexcept
{
    if (!this->initialized_)
        this->Init();

    ImGui::Begin(this->title_.GetString().c_str());

    // TODO: Panel currently doesn't consider the real size of the child items,
    //       it just considers the size of the ImGui items.
    //       This results in a panel size that is too small when using
    //       margin on child items.
    //       This will be fixed when completely reworking the panel
    //       and also considering the size thats given by the parent item.

    bt::Vector2 cursor_position = ImGui::GetCursorPos();
    bt::Vector2 actual_size;

    for (const auto& child : this->child_items_)
    {
        child->Update(cursor_position, bt::Vector2());

        const bt::Vector2 child_size = child->GetSize();

        cursor_position.y += child_size.y + ImGui::GetStyle().ItemSpacing.y;

        if (child_size.x > actual_size.x)
            actual_size.x = child_size.x;
        if (child_size.y > actual_size.y)
            actual_size.y = child_size.y;
    }

    this->actual_size_ = actual_size;
    this->is_hovered_ = ImGui::IsWindowHovered(ImGuiHoveredFlags_ChildWindows);

    ImGui::End();

    this->initialized_ = true;
}

bt::Vector2 Panel::CalcItemSize() const noexcept
{
    bt::Vector2 size;
    for (const auto& child : this->child_items_)
    {
        const bt::Vector2 child_size = child->GetSize();

        if (child_size.x > size.x)
            size.x = child_size.x;
        if (child_size.y > size.y)
            size.y = child_size.y;
    }

    const ImGuiStyle& style = ImGui::GetStyle();

    size.x += style.WindowPadding.x * 2.0f;
    size.y += style.WindowPadding.y * 2.0f;

    return size;
}

void Panel::Init()
{
    ImGui::SetNextWindowPos(this->position_);
    ImGui::SetNextWindowSize(this->size_);

    this->initialized_ = true;
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
    this->title_.GetString() += "##" + this->unique_id_;
    return true;
}

}  // namespace igm::internal
