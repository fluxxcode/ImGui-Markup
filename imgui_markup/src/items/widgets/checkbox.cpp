#include "impch.h"
#include "items/widgets/checkbox.h"

#include "imgui_internal.h"

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
    this->InitAttribute("checked", this->is_checked_);
}

void Checkbox::WidgetUpdate(bt::Vector2 position, bt::Vector2 size) noexcept
{
    ImGui::Checkbox(this->text_.GetString().c_str(),
                    &this->is_checked_.ValueReference());

    this->actual_size_ = ImGui::GetItemRectSize();
    this->is_hovered_ = ImGui::IsItemHovered();

    this->initialized_ = true;
}

bt::Vector2 Checkbox::CalcItemSize() const noexcept
{
    const bt::Vector2 label_size = ImGui::CalcTextSize(
        this->text_.Value().c_str(), NULL, true);

    const ImGuiStyle& style = ImGui::GetStyle();
    ImGuiContext* g = ImGui::GetCurrentContext();

    const float square_sz = g->FontSize + g->Style.FramePadding.y * 2.0f;
    ImVec2 size = ImVec2(square_sz + (label_size.x > 0.0f ?
                                      style.ItemInnerSpacing.x + label_size.x :
                                      0.0f),
                        label_size.y + style.FramePadding.y * 2.0f);

    return size;
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
