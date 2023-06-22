#ifndef IMGUI_MARKUP_SRC_ITEMS_IMGUI_WRAPPER_ITEMS_IM_RADIO_BUTTON_H_
#define IMGUI_MARKUP_SRC_ITEMS_IMGUI_WRAPPER_ITEMS_IM_RADIO_BUTTON_H_

/**
 * @file im_radio_button.h
 * @author FluxxCode (info.fluxxcode@gmail.com)
 * @brief Contains item 'ImRadioButton'
 * @copyright Copyright (c) 2022 - 2023
 */

#include "items/imgui_wrapper_items/im_wrapper_item_base.h"

#include "imgui.h"  // ImGuiMouseButton

namespace igm::internal
{

class ImRadioButton : public ImWrapperItemBase
{
public:
    ImRadioButton(std::string id, ItemBase* parent);

    void ImWrapperUpdate() noexcept;
    void ImRadioButtonUpdate(bool selected) noexcept;

private:
    StringWrapper text_;

    bt::Vector2 position_;
    bt::Vector2 size_;

    bool is_hovered_ = false;

    bt::Vector2 GetSize() const noexcept { return this->size_; };
    bt::Vector2 GetPosition() const noexcept { return this->position_; };

    // API functions
    bool API_IsItemPressed(ImGuiMouseButton btn) noexcept;
    bool API_IsItemHovered() noexcept;

    // See item_base.h for more information
    virtual bool OnProcessStart(std::string& error_message) noexcept;
};

}  // namespace igm::internal

#endif  // IMGUI_MARKUP_SRC_ITEMS_IMGUI_WRAPPER_ITEMS_IM_RADIO_BUTTON_H_
