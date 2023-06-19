#include "impch.h"
#include "items/imgui_wrapper_items/im_child.h"

/**
 * @file im_child.cpp
 * @author FluxxCode (info.fluxxcode@gmail.com)
 * @brief Implementation of im_child.h
 * @copyright Copyright (c) 2022 - 2023
 */

namespace igm::internal
{

ImChild::ImChild(std::string id, ItemBase* parent)
    : ItemBase(ItemType::kImChild, ItemCategory::kImGuiWrapper, id, parent)
{
    this->InitAttribute("id", this->id_);
    this->InitAttribute("size", this->size_overwrite_);
    this->InitAttribute("border", this->border_);
}

void ImChild::ItemUpdate(bt::Vector2 position, bt::Vector2 available_size,
                         bool dynamic_w, bool dynamic_h) noexcept
{
    ImGui::BeginChild(this->id_.GetString().c_str(), this->size_overwrite_,
                      this->border_);

    for (const auto& item : this->child_items_)
        item->Update(position, available_size, dynamic_w, dynamic_h);

    this->position_ = ImGui::GetWindowPos();
    this->size_ =  ImGui::GetWindowSize();
    this->is_hovered_ = ImGui::IsWindowHovered();

    ImGui::EndChild();
}

bool ImChild::API_IsItemPressed(ImGuiMouseButton mb) noexcept
{
    return this->is_hovered_ && ImGui::IsMouseClicked(mb);
}

bool ImChild::API_IsItemHovered() noexcept
{
    return this->is_hovered_;
}

bool ImChild::OnProcessEnd(std::string& error_message) noexcept
{
    if (this->id_.IsValueSet())
        return true;

    this->id_.SetValue("##" + this->unique_id_);
    return true;
}


}  // namespace igm::internal
