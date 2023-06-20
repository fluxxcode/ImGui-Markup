#include "impch.h"
#include "items/imgui_wrapper_items/im_text_colored.h"

/**
 * @file im_text_colored.cpp
 * @author FluxxCode (info.fluxxcode@gmail.com)
 * @brief Implementation of im_text_colored.h
 * @copyright Copyright (c) 2022 - 2023
 */

namespace igm::internal
{

ImTextColored::ImTextColored(std::string id, ItemBase* parent)
    : ImWrapperItemBase(ItemType::kImTextColored, id, parent)
{
    this->InitAttribute("text", this->text_);
    this->InitAttribute("color", this->color_);
}

void ImTextColored::ImWrapperUpdate() noexcept
{
    this->position_ = ImGui::GetCursorPos();

    ImGui::TextColored(this->color_, "%s", this->text_.GetString().c_str());

    this->size_ = ImGui::GetItemRectSize();
    this->is_hovered_ = ImGui::IsItemHovered();

    if (!this->color_.IsValueSet())
    {
        const ImGuiStyle& style = ImGui::GetStyle();
        this->color_ = style.Colors[ImGuiCol_Text];
    }
}

bool ImTextColored::API_IsItemPressed(ImGuiMouseButton mb) noexcept
{
    return this->is_hovered_ && ImGui::IsMouseClicked(mb);
}

bool ImTextColored::API_IsItemHovered() noexcept
{
    return this->is_hovered_;
}

}  // namespace igm::internal
