#include "impch.h"
#include "items/imgui_wrapper_items/im_arrow_button.h"

/**
 * @file im_arrow_button.cpp
 * @author FluxxCode (info.fluxxcode@gmail.com)
 * @brief Implementation of im_arrow_button.h
 * @copyright Copyright (c) 2022 - 2023
 */

namespace igm::internal
{

ImArrowButton::ImArrowButton(std::string id, ItemBase* parent)
    : ImWrapperItemBase(ItemType::kImArrowButton, id, parent)
{
    this->InitAttribute("direction", this->direction_);
}

void ImArrowButton::ImWrapperUpdate() noexcept
{
    this->position_ = ImGui::GetCursorPos();

    ImGui::ArrowButton("",
                       ImGuiDir(static_cast<int>(this->direction_.Value())));

    this->size_ = ImGui::GetItemRectSize();
    this->is_hovered_ = ImGui::IsItemHovered();
}

bool ImArrowButton::API_IsItemPressed(ImGuiMouseButton mb) noexcept
{
    return this->is_hovered_ && ImGui::IsMouseClicked(mb);
}

bool ImArrowButton::API_IsItemHovered() noexcept
{
    return this->is_hovered_;
}

}  // namespace igm::internal
