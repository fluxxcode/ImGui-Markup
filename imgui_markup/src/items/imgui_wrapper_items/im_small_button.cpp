#include "impch.h"
#include "items/imgui_wrapper_items/im_small_button.h"

/**
 * @file im_small_button.cpp
 * @author FluxxCode (info.fluxxcode@gmail.com)
 * @brief Implementation of im_small_button.h
 * @copyright Copyright (c) 2022 - 2023
 */

namespace igm::internal
{

ImSmallButton::ImSmallButton(std::string id, ItemBase* parent)
    : ImWrapperItemBase(ItemType::kImSmallButton, id, parent)
{
    this->InitAttribute("text", this->text_);
}

void ImSmallButton::ImWrapperUpdate() noexcept
{
    this->position_ = ImGui::GetCursorPos();

    ImGui::SmallButton(this->text_.GetString().c_str());

    this->size_ = ImGui::GetItemRectSize();
    this->is_hovered_ = ImGui::IsItemHovered();
}

bool ImSmallButton::API_IsItemPressed(ImGuiMouseButton mb) noexcept
{
    return this->is_hovered_ && ImGui::IsMouseClicked(mb);
}

bool ImSmallButton::API_IsItemHovered() noexcept
{
    return this->is_hovered_;
}

}  // namespace igm::internal
