#include "impch.h"
#include "common/unit.h"

/**
 * @file unit.cpp
 * @author FluxxCode (info.fluxxcode@gmail.com)
 * @brief Implementation of unit.h
 * @copyright Copyright (c) 2022 - 2023
 */

namespace igm::internal
{

Unit::Unit(const size_t unit_id)
    : unit_id_(unit_id)
{
    const void* address = static_cast<const void*>(this);
    std::stringstream ss;
    ss << address;
    this->root_panel_title_ = ss.str();
}

void Unit::Update(size_t display_width, size_t display_height) noexcept
{
    ImGui::SetNextWindowPos(internal::bt::Vector2(0, 0));
    ImGui::SetNextWindowSize(internal::bt::Vector2(display_width,
                                                   display_height));
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
    ImGui::Begin(this->root_panel_title_.c_str(), 0,
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

void Unit::ApplyTheme(Theme& theme) noexcept
{
    for (auto& item : this->item_tree_)
        item->ApplyTheme(theme);
}

std::vector<const char*> Unit::GetItemsOfType(ItemType type) const noexcept
{
    std::vector<const char*> ids = std::vector<const char*>();
    for (auto const& [key, val] : this->item_id_mapping_)
    {
        if (val->GetType() == type)
            ids.push_back(key.c_str());
    }
    return ids;
}

void Unit::Clear() noexcept
{
    this->item_tree_.clear();
    this->item_id_mapping_.clear();
}

}  // namespace igm::internal
