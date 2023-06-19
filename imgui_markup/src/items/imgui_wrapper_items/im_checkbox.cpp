#include "impch.h"
#include "items/imgui_wrapper_items/im_checkbox.h"

/**
 * @file im_checkbox.cpp
 * @author FluxxCode (info.fluxxcode@gmail.com)
 * @brief Implementation of im_checkbox.h
 * @copyright Copyright (c) 2022 - 2023
 */

namespace igm::internal
{

ImCheckbox::ImCheckbox(std::string id, ItemBase* parent)
    : ImWrapperItemBase(ItemType::kImCheckbox, id, parent)
{
    this->InitAttribute("text", this->text_);
}

void ImCheckbox::ImWrapperUpdate() noexcept
{
    this->position_ = ImGui::GetCursorPos();

    ImGui::Checkbox(this->text_.GetString().c_str(), &this->is_checked_);

    this->size_ = ImGui::GetItemRectSize();
    this->is_hovered_ = ImGui::IsItemHovered();
}

bool ImCheckbox::API_IsItemPressed(ImGuiMouseButton mb) noexcept
{
    return this->is_hovered_ && ImGui::IsMouseClicked(mb);
}

bool ImCheckbox::API_IsItemHovered() noexcept
{
    return this->is_hovered_;
}

bool ImCheckbox::API_IsCheckboxChecked() noexcept
{
    return this->is_checked_;
}

}  // namespace igm::internal
