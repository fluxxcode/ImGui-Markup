#include "impch.h"
#include "items/widgets/panel.h"

/**
 * @file panel.cpp
 * @author FluxxCode (info.fluxxcode@gmail.com)
 * @brief Implementation of panel.h
 * @copyright Copyright (c) 2022
 */

namespace igm::internal
{

Panel::Panel(std::string id, ItemBase* parent)
    : WidgetBase(ItemType::kPanel, id, parent)
{ }

void Panel::Update(bt::Vector2 position, bt::Vector2 size) noexcept
{
    ImGui::Begin("HELLO_WORLD");

    for (const auto& child : this->child_items_)
        child->Update(ImGui::GetCursorPos(), bt::Vector2());

    ImGui::End();
}

}  // namespace igm::internal
