#include "impch.h"
#include "items/imgui_wrapper_items/im_label_text.h"

/**
 * @file im_label_text.cpp
 * @author FluxxCode (info.fluxxcode@gmail.com)
 * @brief Implementation of im_label_text.h
 * @copyright Copyright (c) 2022 - 2023
 */

namespace igm::internal
{

ImLabelText::ImLabelText(std::string id, ItemBase* parent)
    : ImWrapperItemBase(ItemType::kImLabelText, id, parent)
{
    this->InitAttribute("text", this->text_);
    this->InitAttribute("label", this->label_);
}

void ImLabelText::ImWrapperUpdate() noexcept
{
    this->position_ = ImGui::GetCursorPos();

    ImGui::LabelText(this->label_.GetString().c_str(), "%s",
                     this->text_.GetString().c_str());

    this->size_ = ImGui::GetItemRectSize();
    this->is_hovered_ = ImGui::IsItemHovered();
}

bool ImLabelText::API_IsItemPressed(ImGuiMouseButton mb) noexcept
{
    return this->is_hovered_ && ImGui::IsMouseClicked(mb);
}

bool ImLabelText::API_IsItemHovered() noexcept
{
    return this->is_hovered_;
}

}  // namespace igm::internal
