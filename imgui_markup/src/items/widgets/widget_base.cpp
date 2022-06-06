#include "impch.h"
#include "items/widgets/widget_base.h"

/**
 * @file widget_base.cpp
 * @author FluxxCode (info.fluxxcode@gmail.com)
 * @brief Implementation of widget_base.h
 * @copyright Copyright (c) 2022
 */

namespace igm::internal
{

void WidgetBase::Update(bt::Vector2 position, bt::Vector2 size) noexcept
{
    ImGui::PushID(this);
    this->WidgetUpdate(position, size);
    ImGui::PopID();
}

void WidgetBase::API_Update(bt::Vector2 position, bt::Vector2 size) noexcept
{
    this->Update(position, size);
}

bool WidgetBase::OnProcessStart(std::string& error_message) noexcept
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
