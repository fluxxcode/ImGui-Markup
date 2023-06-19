#include "impch.h"
#include "items/imgui_wrapper_items/im_spacing.h"

/**
 * @file im_spacing.cpp
 * @author FluxxCode (info.fluxxcode@gmail.com)
 * @brief Implementation of im_spacing.h
 * @copyright Copyright (c) 2022 - 2023
 */

namespace igm::internal
{

ImSpacing::ImSpacing(std::string id, ItemBase* parent)
    : ImWrapperItemBase(ItemType::kImSpacing, id, parent)
{ }

void ImSpacing::ImWrapperUpdate() noexcept
{
    this->position_ = ImGui::GetCursorPos();
    ImGui::Spacing();
}

}  // namespace igm::internal
