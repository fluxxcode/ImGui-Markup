#include "impch.h"
#include "items/gui/views/line_view.h"

/**
 * @file line_view.cpp
 * @author FluxxCode (info.fluxxcode@gmail.com)
 * @brief Implementation of im_line_view.h
 * @copyright Copyright (c) 2022
 */

namespace igm::internal
{

LineView::LineView(std::string id, ItemBase* parent)
    : ViewBase(ItemType::kLineView, id, parent)
{
    this->InitAttribute("padding", this->padding_);
    this->InitAttribute("margin", this->margin_);
    this->InitAttribute("spacing", this->spacing_);
}

void LineView::Update(bt::Vector2 position, bt::Vector2 available_size,
                      bool dynamic_w, bool dynamic_h) noexcept
{
    const bt::Padding& padding = this->padding_.ValueReference();
    const bt::Margin& margin = this->margin_.ValueReference();

    position.x += margin.left;
    position.y += margin.top;

    this->cursor_position_ = position;
    this->cursor_position_.x += padding.left;
    this->cursor_position_.y += padding.top;

    for (const auto& child : this->child_items_)
        child->Update(ImGui::GetCursorPos(), bt::Vector2(0.0f, 0.0f),
                      true, true);
}

bool LineView::OnProcessStart(std::string& error_message) noexcept
{
    const ItemBase* parent = this->parent_;
    while (parent)
    {
        if (parent->GetType() == ItemType::kPanel)
            return true;

        parent = parent->GetParent();
    }

    error_message = "One of the items parent item must be an item "
                    "of type Panel";
    return false;
}

}  // namespace igm::internal
