#include "impch.h"
#include "items/root_item.h"

/**
 * @file root_item.cpp
 * @author FluxxCode (info.fluxxcode@gmail.com)
 * @brief Implementation of root_item.h
 * @copyright Copyright (c) 2022
 */

#include "imgui_internal.h"

namespace igm::internal
{

RootItem::RootItem()
{
    const void* address = static_cast<const void*>(this);
    std::stringstream ss;
    ss << address;
    this->root_panel_title_ = ss.str().c_str();
}

void RootItem::Update(size_t display_width, size_t display_height) noexcept
{
    ImGui::SetNextWindowPos(internal::bt::Vector2(0, 0));
    ImGui::SetNextWindowSize(internal::bt::Vector2(display_width,
                                                   display_height));
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
    ImGui::Begin(this->root_panel_title_, 0,
                 ImGuiWindowFlags_NoBringToFrontOnFocus |
                 ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize |
                 ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoDecoration);

    ImGui::PopStyleVar();

    for (const auto& child : this->item_tree_)
    {
        child->API_Update(internal::bt::Vector2(0, 0),
                          internal::bt::Vector2(display_width, display_height));
    }

    ImGui::End();
}

void RootItem::Clear() noexcept
{
    this->item_tree_.clear();
}

}  // namespace igm::internal
