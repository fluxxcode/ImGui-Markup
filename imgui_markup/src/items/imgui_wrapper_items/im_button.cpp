#include "impch.h"
#include "items/imgui_wrapper_items/im_button.h"

/**
 * @file im_button.cpp
 * @author FluxxCode (info.fluxxcode@gmail.com)
 * @brief Implementation of im_button.h
 * @copyright Copyright (c) 2022 - 2023
 */

namespace igm::internal
{

ImButton::ImButton(std::string id, ItemBase* parent)
    : ImWrapperItemBase(ItemType::kImButton, id, parent)
{
    this->InitAttribute("text", this->text_);
    this->InitAttribute("size", this->size_overwrite_);
}

void ImButton::ImWrapperUpdate() noexcept
{
    this->position_ = ImGui::GetCursorPos();

    ImGui::Button(this->text_.GetString().c_str(), this->size_overwrite_);

    this->size_ = ImGui::GetItemRectSize();
    this->is_hovered_ = ImGui::IsItemHovered();
}

bool ImButton::API_IsItemPressed(ImGuiMouseButton mb) noexcept
{
    return this->is_hovered_ && ImGui::IsMouseClicked(mb);
}

bool ImButton::API_IsItemHovered() noexcept
{
    return this->is_hovered_;
}

}  // namespace igm::internal
