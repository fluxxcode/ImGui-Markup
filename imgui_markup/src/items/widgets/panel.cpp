#include "impch.h"
#include "items/widgets/panel.h"

/**
 * @file panel.cpp
 * @author FluxxCode (info.fluxxcode@gmail.com)
 * @brief Implementation of panel.h
 * @copyright Copyright (c) 2022
 */

namespace igm::internal
{

Panel::Panel(std::string id, ItemBase* parent)
    : WidgetBase(ItemType::kPanel, id, parent)
{
    this->InitAttribute("title", this->title_);
    this->InitAttribute("position", this->position_);
    this->InitAttribute("size", this->size_);
}

void Panel::Update(bt::Vector2 position, bt::Vector2 size) noexcept
{
    if (!this->init_)
        this->Init();

    ImGui::Begin(this->title_.GetString().c_str());

    for (const auto& child : this->child_items_)
        child->Update(ImGui::GetCursorPos(), bt::Vector2());

    this->is_hovered_ = ImGui::IsWindowHovered(ImGuiHoveredFlags_ChildWindows);

    ImGui::End();
}

void Panel::Init()
{
    ImGui::SetNextWindowPos(this->position_);
    ImGui::SetNextWindowSize(this->size_);

    this->init_ = true;
}

bool Panel::API_IsPressed(ImGuiMouseButton mb) noexcept
{
    return this->is_hovered_ && ImGui::IsMouseClicked(mb);
}

bool Panel::API_IsHovered() noexcept
{
    return this->is_hovered_;
}

bool Panel::OnProcessEnd(std::string& error_message) noexcept
{
    this->title_.GetString() += "##" + this->unique_id_;
    return true;
}

}  // namespace igm::internal
