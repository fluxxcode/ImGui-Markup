#include "impch.h"
#include "items/imgui_wrapper_items/im_invisible_button.h"

/**
 * @file im_invisible_button.cpp
 * @author FluxxCode (info.fluxxcode@gmail.com)
 * @brief Implementation of im_invisible_button.h
 * @copyright Copyright (c) 2022 - 2023
 */

namespace igm::internal
{

ImInvisibleButton::ImInvisibleButton(std::string id, ItemBase* parent)
    : ImWrapperItemBase(ItemType::kImInvisibleButton, id, parent)
{
    this->InitAttribute("size", this->size_overwrite_);
}

void ImInvisibleButton::ImWrapperUpdate() noexcept
{
    this->position_ = ImGui::GetCursorPos();

    ImGui::InvisibleButton("", this->size_overwrite_);

    this->size_ = ImGui::GetItemRectSize();
    this->is_hovered_ = ImGui::IsItemHovered();
}

bool ImInvisibleButton::API_IsItemPressed(ImGuiMouseButton mb) noexcept
{
    return this->is_hovered_ && ImGui::IsMouseClicked(mb);
}

bool ImInvisibleButton::API_IsItemHovered() noexcept
{
    return this->is_hovered_;
}

}  // namespace igm::internal
