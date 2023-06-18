#include "impch.h"
#include "items/style/text_style.h"

/**
 * @file text_style.cpp
 * @author FluxxCode (info.fluxxcode@gmail.com)
 * @brief Implementation of text_style.h
 * @copyright Copyright (c) 2022 - 2023
 */

namespace igm::internal
{

TextStyle::TextStyle(std::string id, ItemBase* parent)
    : StyleBase(ItemType::kTextStyle, id, parent, ItemType::kText)
{
    this->InitAttribute("color", this->color_);
    this->InitAttribute("color_hovered", this->color_hovered_);
    this->InitAttribute("color_active", this->color_active_);
}

void TextStyle::PushStyle(ItemBase& item) const noexcept
{
    // TODO: Add attribute to set which MouseButton is used
    if (this->color_active_.IsValueSet() && item.API_IsItemHovered() &&
        ImGui::IsMouseDown(ImGuiMouseButton_Left))
    {
        this->PushStyleColor(ImGuiCol_Text, this->color_active_);
    }
    else if (this->color_hovered_.IsValueSet() && item.API_IsItemHovered())
        this->PushStyleColor(ImGuiCol_Text, this->color_hovered_);
    else if (this->color_.IsValueSet())
        this->PushStyleColor(ImGuiCol_Text, this->color_);
}

void TextStyle::PopStyle() const noexcept
{
    this->PopStyleColor();
}

}  // namespace igm::internal
