#include "impch.h"
#include "items/widgets/checkbox.h"

/**
 * @file checkbox.cpp
 * @author FluxxCode (info.fluxxcode@gmail.com)
 * @brief Implementation of checkbox.h
 * @copyright Copyright (c) 2022
 */

namespace igm::internal
{

Checkbox::Checkbox(std::string id, ItemBase* parent)
    : WidgetBase(ItemType::kCheckbox, id, parent)
{
    this->InitAttribute("text", this->text_);
}

void Checkbox::WidgetUpdate(bt::Vector2 position, bt::Vector2 size) noexcept
{
    ImGui::Checkbox(this->text_.GetString().c_str(), &this->is_checked_);

    this->is_hovered_ = ImGui::IsItemHovered();
}

bool Checkbox::API_IsItemPressed(ImGuiMouseButton mb) noexcept
{
    return this->is_hovered_ && ImGui::IsMouseClicked(mb);
}

bool Checkbox::API_IsItemHovered() noexcept
{
    return this->is_hovered_;
}

bool Checkbox::API_IsCheckboxChecked() noexcept
{
    return this->is_checked_;
}

}  // namespace igm::internal
