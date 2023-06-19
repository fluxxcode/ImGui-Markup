#include "impch.h"
#include "items/imgui_wrapper_items/im_text.h"

/**
 * @file im_text.cpp
 * @author FluxxCode (info.fluxxcode@gmail.com)
 * @brief Implementation of im_text.h
 * @copyright Copyright (c) 2022 - 2023
 */

namespace igm::internal
{

ImText::ImText(std::string id, ItemBase* parent)
    : ImWrapperItemBase(ItemType::kImText, id, parent)
{
    this->InitAttribute("text", this->text_);
}

void ImText::ItemUpdate(bt::Vector2 position, bt::Vector2 available_size,
                        bool dynamic_w, bool dynamic_h) noexcept
{
    this->position_ = ImGui::GetCursorPos();

    ImGui::Text("%s", this->text_.GetString().c_str());

    this->size_ = ImGui::GetItemRectSize();
    this->is_hovered_ = ImGui::IsItemHovered();
}

bool ImText::API_IsItemPressed(ImGuiMouseButton mb) noexcept
{
    return this->is_hovered_ && ImGui::IsMouseClicked(mb);
}

bool ImText::API_IsItemHovered() noexcept
{
    return this->is_hovered_;
}

}  // namespace igm::internal
