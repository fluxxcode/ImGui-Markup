#include "impch.h"
#include "common/units/gui_unit.h"

/**
 * @file gui_unit.cpp
 * @author FluxxCode (info.fluxxcode@gmail.com)
 * @brief Implementation of gui_unit.h
 * @copyright Copyright (c) 2022
 */

namespace igm::internal
{

GUIUnit::GUIUnit(const size_t unit_id)
    : UnitBase(unit_id, UnitType::kGUI)
{
    const void* address = static_cast<const void*>(this);
    std::stringstream ss;
    ss << address;
    this->root_panel_title_ = ss.str();
}

void GUIUnit::Update(size_t display_width, size_t display_height) noexcept
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

}  // namespace igm::internal
