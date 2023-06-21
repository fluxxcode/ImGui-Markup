#include "impch.h"
#include "items/imgui_wrapper_items/im_text_wrapped.h"

/**
 * @file im_text_wrapped.cpp
 * @author FluxxCode (info.fluxxcode@gmail.com)
 * @brief Implementation of im_text_wrapped.h
 * @copyright Copyright (c) 2022 - 2023
 */

namespace igm::internal
{

ImTextWrapped::ImTextWrapped(std::string id, ItemBase* parent)
    : ImWrapperItemBase(ItemType::kImTextWrapped, id, parent)
{
    this->InitAttribute("text", this->text_);
}

void ImTextWrapped::ImWrapperUpdate() noexcept
{
    this->position_ = ImGui::GetCursorPos();

    ImGui::TextWrapped("%s", this->text_.GetString().c_str());

    this->size_ = ImGui::GetItemRectSize();
    this->is_hovered_ = ImGui::IsItemHovered();
}

bool ImTextWrapped::API_IsItemPressed(ImGuiMouseButton mb) noexcept
{
    return this->is_hovered_ && ImGui::IsMouseClicked(mb);
}

bool ImTextWrapped::API_IsItemHovered() noexcept
{
    return this->is_hovered_;
}

}  // namespace igm::internal
