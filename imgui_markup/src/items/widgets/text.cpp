#include "impch.h"
#include "items/widgets/text.h"

/**
 * @file text.cpp
 * @author FluxxCode (info.fluxxcode@gmail.com)
 * @brief Implementation of text.h
 * @copyright Copyright (c) 2022
 */

namespace igm::internal
{

Text::Text(std::string id, ItemBase* parent)
    : WidgetBase(ItemType::kButton, id, parent)
{
    this->InitAttribute("text", this->text_);
}

void Text::WidgetUpdate(bt::Vector2 position, bt::Vector2 size) noexcept
{
    ImGui::Text("%s", this->text_.GetString().c_str());

    this->is_hovered_ = ImGui::IsItemHovered();
}

bool Text::API_IsPressed(ImGuiMouseButton mb) noexcept
{
    return this->is_hovered_ && ImGui::IsMouseClicked(mb);
}

bool Text::API_IsHovered() noexcept
{
    return this->is_hovered_;
}

}  // namespace igm::internal
