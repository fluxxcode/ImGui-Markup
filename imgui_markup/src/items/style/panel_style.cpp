#include "impch.h"
#include "items/style/panel_style.h"

/**
 * @file panel_style.cpp
 * @author FluxxCode (info.fluxxcode@gmail.com)
 * @brief Implementation of panel_style.h
 * @copyright Copyright (c) 2022 - 2023
 */

namespace igm::internal
{

PanelStyle::PanelStyle(std::string id, ItemBase* parent)
    : StyleBase(ItemType::kPanelStyle, id, parent, ItemType::kPanel)
{
    this->InitAttribute("color", this->color_);
    this->InitAttribute("color_hovered", this->color_hovered_);
    this->InitAttribute("color_active", this->color_active_);
}

void PanelStyle::PushStyle(ItemBase& item) const noexcept
{
    // TODO: Add attribute to set which MouseButton is used
    if (this->color_active_.IsValueSet() && item.API_IsItemHovered() &&
        ImGui::IsMouseDown(ImGuiMouseButton_Left))
    {
        this->PushStyleColor(ImGuiCol_WindowBg, this->color_active_);
    }
    else if (this->color_hovered_.IsValueSet() && item.API_IsItemHovered())
        this->PushStyleColor(ImGuiCol_WindowBg, this->color_hovered_);
    else if (this->color_.IsValueSet())
        this->PushStyleColor(ImGuiCol_WindowBg, this->color_);
}

void PanelStyle::PopStyle() const noexcept
{
    this->PopStyleColor();
}

}  // namespace igm::internal
