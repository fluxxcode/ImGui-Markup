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

    this->actual_size_ = ImGui::GetItemRectSize();
    this->is_hovered_ = ImGui::IsItemHovered();

    this->initialized_ = true;
}

bt::Vector2 Text::CalcItemSize() const noexcept
{
    return ImGui::CalcTextSize(this->text_.GetValue().c_str(), NULL, true);
}

bool Text::API_IsItemPressed(ImGuiMouseButton mb) noexcept
{
    return this->is_hovered_ && ImGui::IsMouseClicked(mb);
}

bool Text::API_IsItemHovered() noexcept
{
    return this->is_hovered_;
}

}  // namespace igm::internal
