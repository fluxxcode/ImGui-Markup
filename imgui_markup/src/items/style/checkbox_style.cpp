#include "impch.h"
#include "items/style/checkbox_style.h"

/**
 * @file checkbox_style.cpp
 * @author FluxxCode (info.fluxxcode@gmail.com)
 * @brief Implementation of checkbox_style.h
 * @copyright Copyright (c) 2023
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

void CheckboxStyle::PopStyle() const noexcept
{
    ImGui::PopStyleColor(1);
}

}  // namespace igm::internal
