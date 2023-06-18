#include "impch.h"
#include "items/gui/widgets/widget_base.h"

/**
 * @file widget_base.cpp
 * @author FluxxCode (info.fluxxcode@gmail.com)
 * @brief Implementation of widget_base.h
 * @copyright Copyright (c) 2022 - 2023
 */

#include "imgui_internal.h"

namespace igm::internal
{

WidgetBase::WidgetBase(ItemType type, std::string id, ItemBase* parent,
                       bool clipping_area)
    : GUIBase(type, ItemCategory::kWidget, id, parent, clipping_area)
{ }

void WidgetBase::GUIUpdate(bt::Vector2 position, bt::Vector2 size) noexcept
{
    ImGui::PushID(this);
    ImGui::SetCursorPos(position);
    this->WidgetUpdate(position, size);
    ImGui::PopID();
}

}  // namespace igm::internal
