#include "impch.h"
#include "items/imgui_wrapper_items/im_same_line.h"

/**
 * @file im_same_line.cpp
 * @author FluxxCode (info.fluxxcode@gmail.com)
 * @brief Implementation of im_same_line.h
 * @copyright Copyright (c) 2022 - 2023
 */

namespace igm::internal
{

ImSameLine::ImSameLine(std::string id, ItemBase* parent)
    : ImWrapperItemBase(ItemType::kImSameLine, id, parent)
{
    this->InitAttribute("offset_from_start_x", this->offset_from_start_x_);
    this->InitAttribute("spacing", this->spacing_);
}

void ImSameLine::ImWrapperUpdate() noexcept
{
    ImGui::SameLine(this->offset_from_start_x_, this->spacing_);
    this->position_ = ImGui::GetCursorPos();
}

}  // namespace igm::internal
