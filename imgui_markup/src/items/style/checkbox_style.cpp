#include "impch.h"
#include "items/style/checkbox_style.h"

/**
 * @file checkbox_style.cpp
 * @author FluxxCode (info.fluxxcode@gmail.com)
 * @brief Implementation of checkbox_style.h
 * @copyright Copyright (c) 2022 - 2023
 */

namespace igm::internal
{

CheckboxStyle::CheckboxStyle(std::string id, ItemBase* parent)
    : StyleBase(ItemType::kCheckboxStyle, id, parent, ItemType::kCheckbox)
{
    this->InitAttribute("text_color", this->text_color_);
    this->InitAttribute("text_color_hovered",
        this->text_color_hovered_);
    this->InitAttribute("text_color_active",
        this->text_color_active_);
}

void CheckboxStyle::PushStyle(ItemBase& item) const noexcept
{
    // TODO: Add attribute to set which MouseButton is used
    if (this->text_color_active_.IsValueSet() && item.API_IsItemHovered() &&
        ImGui::IsMouseDown(ImGuiMouseButton_Left))
    {
        this->PushStyleColor(ImGuiCol_Text, this->text_color_active_);
    }
    else if (this->text_color_hovered_.IsValueSet() && item.API_IsItemHovered())
        this->PushStyleColor(ImGuiCol_Text, this->text_color_hovered_);
    else if (this->text_color_.IsValueSet())
        this->PushStyleColor(ImGuiCol_Text, this->text_color_);
}

void CheckboxStyle::PopStyle() const noexcept
{
    this->PopStyleColor();
}

}  // namespace igm::internal
