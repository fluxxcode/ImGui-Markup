#include "impch.h"
#include "items/imgui_wrapper_items/im_window.h"

/**
 * @file im_window.cpp
 * @author FluxxCode (info.fluxxcode@gmail.com)
 * @brief Implementation of im_window.h
 * @copyright Copyright (c) 2022 - 2023
 */

namespace igm::internal
{

ImWindow::ImWindow(std::string id, ItemBase* parent)
    : ImWrapperItemBase(ItemType::kImWindow, id, parent)
{
    this->InitAttribute("name", this->name_);
}

void ImWindow::ItemUpdate(bt::Vector2 position, bt::Vector2 available_size,
                          bool dynamic_w, bool dynamic_h) noexcept
{
    ImGui::Begin(this->name_.GetString().c_str());

    for (const auto& item : this->child_items_)
        item->Update(position, available_size, dynamic_w, dynamic_h);

    this->position_ = ImGui::GetWindowPos();
    this->size_ = ImGui::GetWindowSize();
    this->is_hovered_ = ImGui::IsWindowHovered();

    ImGui::End();
}

bool ImWindow::API_IsItemPressed(ImGuiMouseButton mb) noexcept
{
    return this->is_hovered_ && ImGui::IsMouseClicked(mb);
}

bool ImWindow::API_IsItemHovered() noexcept
{
    return this->is_hovered_;
}

bool ImWindow::OnProcessEnd(std::string& error_message) noexcept
{
    if (this->name_.IsValueSet())
        return true;

    this->name_.SetValue(this->unique_id_);
    return true;
}

}  // namespace igm::internal
