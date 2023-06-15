#include "impch.h"
#include "items/style/button_style.h"

/**
 * @file button_style.cpp
 * @author FluxxCode (info.fluxxcode@gmail.com)
 * @brief Implementation of button_style.h
 * @copyright Copyright (c) 2023
 */

namespace igm::internal
{

ButtonStyle::ButtonStyle(std::string id, ItemBase* parent)
    : StyleBase(ItemType::kButtonStyle, id, parent, ItemType::kButton)
{
    this->InitAttribute("color", this->color_);
    this->InitAttribute("color_hovered", this->color_hovered_);
    this->InitAttribute("color_active", this->color_active_);
    this->InitAttribute("text_color", this->text_color_);
    this->InitAttribute("text_color_hovered",
        this->text_color_hovered_);
    this->InitAttribute("text_color_active",
        this->text_color_active_);
}

void ButtonStyle::PushStyle(ItemBase& item) const noexcept
{
    ImGui::PushStyleColor(ImGuiCol_Button, this->color_);
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, this->color_hovered_);
    ImGui::PushStyleColor(ImGuiCol_ButtonActive, this->color_active_);

    // TODO: Add attribute to set which MouseButton is used
    if (item.API_IsItemHovered() &&
        ImGui::IsMouseDown(ImGuiMouseButton_Left))
    {
        ImGui::PushStyleColor(ImGuiCol_Text, this->text_color_active_);
    }
    else if (item.API_IsItemHovered())
        ImGui::PushStyleColor(ImGuiCol_Text, this->text_color_hovered_);
    else
        ImGui::PushStyleColor(ImGuiCol_Text, this->text_color_);
}

void ButtonStyle::PopStyle() const noexcept
{
    ImGui::PopStyleColor(4);
}

}  // namespace igm::internal
