#include "impch.h"
#include "items/imgui_wrapper_items/im_text_disabled.h"

/**
 * @file im_text_disabled.cpp
 * @author FluxxCode (info.fluxxcode@gmail.com)
 * @brief Implementation of im_text_disabled.h
 * @copyright Copyright (c) 2022 - 2023
 */

namespace igm::internal
{

ImTextDisabled::ImTextDisabled(std::string id, ItemBase* parent)
    : ImWrapperItemBase(ItemType::kImTextDisabled, id, parent)
{
    this->InitAttribute("text", this->text_);
}

void ImTextDisabled::ImWrapperUpdate() noexcept
{
    this->position_ = ImGui::GetCursorPos();

    ImGui::TextDisabled("%s", this->text_.GetString().c_str());

    this->size_ = ImGui::GetItemRectSize();
    this->is_hovered_ = ImGui::IsItemHovered();
}

bool ImTextDisabled::API_IsItemPressed(ImGuiMouseButton mb) noexcept
{
    return this->is_hovered_ && ImGui::IsMouseClicked(mb);
}

bool ImTextDisabled::API_IsItemHovered() noexcept
{
    return this->is_hovered_;
}

}  // namespace igm::internal
