#include "impch.h"
#include "items/widgets/button.h"

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
    this->InitAttribute("size", this->size_);
}

void Button::Update(bt::Vector2 position, bt::Vector2 size) noexcept
{
    ImGui::Button(this->text_.GetString().c_str(), this->size_);

    this->is_hovered_ = ImGui::IsItemHovered();
}

bool Button::API_IsPressed(ImGuiMouseButton mb) noexcept
{
    return this->is_hovered_ && ImGui::IsMouseClicked(mb);
}

bool Button::API_IsHovered() noexcept
{
    return this->is_hovered_;
}

bool Button::OnProcessStart(std::string& error_message)
{
    return true;
}

}  // namespace igm::internal
