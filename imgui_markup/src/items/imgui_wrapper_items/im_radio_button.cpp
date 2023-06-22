#include "impch.h"
#include "items/imgui_wrapper_items/im_radio_button.h"

/**
 * @file im_radio_button.cpp
 * @author FluxxCode (info.fluxxcode@gmail.com)
 * @brief Implementation of im_radio_button.h
 * @copyright Copyright (c) 2022 - 2023
 */

namespace igm::internal
{

ImRadioButton::ImRadioButton(std::string id, ItemBase* parent)
    : ImWrapperItemBase(ItemType::kImRadioButton, id, parent)
{
    this->InitAttribute("text", this->text_);
}

void ImRadioButton::ImWrapperUpdate() noexcept
{
    this->ImRadioButtonUpdate(false);
}

void ImRadioButton::ImRadioButtonUpdate(bool selected) noexcept
{
    this->position_ = ImGui::GetCursorPos();

    ImGui::RadioButton(this->text_.GetString().c_str(), selected);

    this->size_ = ImGui::GetItemRectSize();
    this->is_hovered_ = ImGui::IsItemHovered();
}

bool ImRadioButton::API_IsItemPressed(ImGuiMouseButton mb) noexcept
{
    return this->is_hovered_ && ImGui::IsMouseClicked(mb);
}

bool ImRadioButton::API_IsItemHovered() noexcept
{
    return this->is_hovered_;
}

bool ImRadioButton::OnProcessStart(std::string& error_message) noexcept
{
    const ItemBase* parent = this->GetParent();
    if (parent)
    {
        if (parent->GetType() == ItemType::kImRadioSelection)
            return true;
    }
    error_message = "Item of type RadioButton can only be placed inside an "
                    "item of type RadioSelection.";
    return false;
}

}  // namespace igm::internal
