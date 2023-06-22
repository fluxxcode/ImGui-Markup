#include "impch.h"
#include "items/imgui_wrapper_items/im_radio_selection.h"

/**
 * @file im_radio_selection.cpp
 * @author FluxxCode (info.fluxxcode@gmail.com)
 * @brief Implementation of im_radio_selection.h
 * @copyright Copyright (c) 2022 - 2023
 */

#include "items/imgui_wrapper_items/im_radio_button.h"

namespace igm::internal
{

ImRadioSelection::ImRadioSelection(std::string id, ItemBase* parent)
    : ImWrapperItemBase(ItemType::kImRadioSelection, id, parent)
{
    this->InitAttribute("selected", this->selected_);
}

void ImRadioSelection::ImWrapperUpdate() noexcept
{
    this->position_ = ImGui::GetCursorPos();

    bt::Vector2 size = bt::Vector2(0.0f, 0.0f);

    size_t index = 0;
    for (const auto& child : this->child_items_)
    {
        if (ImGui::GetCursorPosX() < this->position_.x)
            ImGui::SetCursorPosX(this->position_.x);

        if (child->GetType() == ItemType::kImRadioButton)
        {
            ImRadioButton* r_btn = dynamic_cast<ImRadioButton*>(child);
            r_btn->ImRadioButtonUpdate(this->selected_ == index);
            if (child->API_IsItemPressed())
                this->selected_ = index; 
        }
        else
            child->Update(bt::Vector2(), bt::Vector2(), true, true);

        const bt::Vector2 child_size = child->GetSize();
        const bt::Vector2 child_position = child->GetPosition();

        // Calc rect max
        if (child_position.x + child_size.x > this->position_.x + size.x)
            size.x = child_position.x + child_size.x - this->position_.x;
        if (child_position.y + child_size.y > this->position_.y + size.y)
            size.y = child_position.y + child_size.y - this->position_.y;

        // TODO: Maybe calc rect min

       index++;
    }

    this->size_ = size;

    const ImVec2 min = this->position_;
    const ImVec2 max = ImVec2(this->position_.x + size.x,
                              this->position_.y + size.y);

    // TODO: Use childs.API_IsItemHovered to check if the
    //       radio selection is hovered.
    this->is_hovered_ = ImGui::IsMouseHoveringRect(min, max);
}

bool ImRadioSelection::API_IsItemPressed(ImGuiMouseButton mb) noexcept
{
    return this->is_hovered_ && ImGui::IsMouseClicked(mb);
}

bool ImRadioSelection::API_IsItemHovered() noexcept
{
    return this->is_hovered_;
}

int ImRadioSelection::API_GetSelected() noexcept
{
    return this->selected_;
}

}  // namespace igm::internal
