#include "impch.h"
#include "items/imgui_wrapper_items/im_separator.h"

/**
 * @file im_separator.cpp
 * @author FluxxCode (info.fluxxcode@gmail.com)
 * @brief Implementation of im_separator.h
 * @copyright Copyright (c) 2022 - 2023
 */

namespace igm::internal
{

ImSeparator::ImSeparator(std::string id, ItemBase* parent)
    : ImWrapperItemBase(ItemType::kImSeparator, id, parent)
{ }

void ImSeparator::ImWrapperUpdate() noexcept
{
    this->position_ = ImGui::GetCursorPos();

    ImGui::Separator();

    this->size_ = ImGui::GetItemRectSize();
    this->is_hovered_ = ImGui::IsItemHovered();
}

bool ImSeparator::API_IsItemPressed(ImGuiMouseButton mb) noexcept
{
    return this->is_hovered_ && ImGui::IsMouseClicked(mb);
}

bool ImSeparator::API_IsItemHovered() noexcept
{
    return this->is_hovered_;
}

}  // namespace igm::internal
