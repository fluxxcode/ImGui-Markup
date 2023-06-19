#include "impch.h"
#include "items/imgui_wrapper_items/im_dummy.h"

/**
 * @file im_dummy.cpp
 * @author FluxxCode (info.fluxxcode@gmail.com)
 * @brief Implementation of im_dummy.h
 * @copyright Copyright (c) 2022 - 2023
 */

namespace igm::internal
{

ImDummy::ImDummy(std::string id, ItemBase* parent)
    : ImWrapperItemBase(ItemType::kImDummy, id, parent)
{
    this->InitAttribute("size", this->size_overwrite_);
}

void ImDummy::ImWrapperUpdate() noexcept
{
    this->position_ = ImGui::GetCursorPos();

    ImGui::Dummy(this->size_overwrite_);

    this->size_ = ImGui::GetItemRectSize();
    this->is_hovered_ = ImGui::IsItemHovered();
}

bool ImDummy::API_IsItemPressed(ImGuiMouseButton mb) noexcept
{
    return this->is_hovered_ && ImGui::IsMouseClicked(mb);
}

bool ImDummy::API_IsItemHovered() noexcept
{
    return this->is_hovered_;
}

}  // namespace igm::internal
