#include "impch.h"
#include "items/views/line_view.h"

/**
 * @file im_line_view.cpp
 * @author FluxxCode (info.fluxxcode@gmail.com)
 * @brief Implementation of im_line_view.h
 * @copyright Copyright (c) 2022
 */

namespace igm::internal
{

LineView::LineView(std::string id, ItemBase* parent)
    : ViewBase(ItemType::kLineView, id, parent)
{ }

void LineView::Update(bt::Vector2 position, bt::Vector2 size) noexcept
{
    for (const auto& child : this->child_items_)
        child->Update(ImGui::GetCursorPos(), bt::Vector2(0.0f, 0.0f));
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