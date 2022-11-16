#include "impch.h"
#include "items/style/text_style.h"

/**
 * @file text_style.cpp
 * @author FluxxCode (info.fluxxcode@gmail.com)
 * @brief Implementation of text_style.h
 * @copyright Copyright (c) 2022
 */

namespace igm::internal
{

TextStyle::TextStyle(std::string id, ItemBase* parent)
    : StyleBase(ItemType::kTextStyle, id, parent, ItemType::kText)
{
    this->InitAttribute("color", this->color_);
}

void TextStyle::PushStyle() const noexcept
{
    ImGui::PushStyleColor(ImGuiCol_Text, this->color_);
}

void TextStyle::PopStyle() const noexcept
{
    ImGui::PopStyleColor(1);
}

}  // namespace igm::internal
