#include "impch.h"
#include "items/imgui_wrapper_items/im_group.h"

/**
 * @file im_group.cpp
 * @author FluxxCode (info.fluxxcode@gmail.com)
 * @brief Implementation of im_group.h
 * @copyright Copyright (c) 2022 - 2023
 */

namespace igm::internal
{

ImGroup::ImGroup(std::string id, ItemBase* parent)
    : ItemBase(ItemType::kImGroup, ItemCategory::kImGuiWrapper, id, parent)
{ }

void ImGroup::ItemUpdate(bt::Vector2 position, bt::Vector2 available_size,
                         bool dynamic_w, bool dynamic_h) noexcept
{
    this->position_ = ImGui::GetCursorPos();

    ImGui::BeginGroup();

    for (const auto& item : this->child_items_)
        item->Update(position, available_size, dynamic_w, dynamic_h);

    ImGui::EndGroup();

    this->is_hovered_ = ImGui::IsItemHovered();
    this->size_ = ImGui::GetItemRectSize();
}

bool ImGroup::API_IsItemPressed(ImGuiMouseButton mb) noexcept
{
    return this->is_hovered_ && ImGui::IsMouseClicked(mb);
}

bool ImGroup::API_IsItemHovered() noexcept
{
    return this->is_hovered_;
}

}  // namespace igm::internal
