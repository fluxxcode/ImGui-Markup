#include "impch.h"
#include "items/imgui_wrapper_items/im_bullet_text.h"

/**
 * @file im_bullet_text.cpp
 * @author FluxxCode (info.fluxxcode@gmail.com)
 * @brief Implementation of im_bullet_text.h
 * @copyright Copyright (c) 2022 - 2023
 */

namespace igm::internal
{

ImBulletText::ImBulletText(std::string id, ItemBase* parent)
    : ImWrapperItemBase(ItemType::kImBulletText, id, parent)
{
    this->InitAttribute("text", this->text_);
}

void ImBulletText::ImWrapperUpdate() noexcept
{
    this->position_ = ImGui::GetCursorPos();

    ImGui::BulletText("%s", this->text_.GetString().c_str());

    this->size_ = ImGui::GetItemRectSize();
    this->is_hovered_ = ImGui::IsItemHovered();
}

bool ImBulletText::API_IsItemPressed(ImGuiMouseButton mb) noexcept
{
    return this->is_hovered_ && ImGui::IsMouseClicked(mb);
}

bool ImBulletText::API_IsItemHovered() noexcept
{
    return this->is_hovered_;
}

}  // namespace igm::internal
