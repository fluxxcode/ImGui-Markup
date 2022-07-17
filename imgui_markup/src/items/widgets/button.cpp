#include "impch.h"
#include "items/widgets/button.h"

#include "imgui_internal.h"

/**
 * @file button.cpp
 * @author FluxxCode (info.fluxxcode@gmail.com)
 * @brief Implementation of button.h
 * @copyright Copyright (c) 2022
 */

namespace igm::internal
{

Button::Button(std::string id, ItemBase* parent)
    : WidgetBase(ItemType::kButton, id, parent)
{
    this->InitAttribute("text", this->text_);
}

void Button::WidgetUpdate(bt::Vector2 position, bt::Vector2 size) noexcept
{
    ImGui::Button(this->text_.GetString().c_str(), size);

    this->actual_size_ = ImGui::GetItemRectSize();
    this->is_hovered_ = ImGui::IsItemHovered();

    this->initialized_ = true;
}

bt::Vector2 Button::CalcItemSize() const noexcept
{
    const bt::Vector2 label_size = ImGui::CalcTextSize(
        this->text_.Value().c_str(), NULL, true);

    const ImGuiStyle& style = ImGui::GetStyle();

    ImVec2 size = ImGui::CalcItemSize(ImVec2(0.0f, 0.0f),
        label_size.x + style.FramePadding.x * 2.0f,
        label_size.y + style.FramePadding.y * 2.0f);

    return size;
}

bool Button::API_IsItemPressed(ImGuiMouseButton mb) noexcept
{
    return this->is_hovered_ && ImGui::IsMouseClicked(mb);
}

bool Button::API_IsItemHovered() noexcept
{
    return this->is_hovered_;
}

}  // namespace igm::internal
