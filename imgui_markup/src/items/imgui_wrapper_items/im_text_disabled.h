#ifndef IMGUI_MARKUP_SRC_ITEMS_IMGUI_WRAPPER_ITEMS_IM_TEXT_DISABLED_H_
#define IMGUI_MARKUP_SRC_ITEMS_IMGUI_WRAPPER_ITEMS_IM_TEXT_DISABLED_H_

/**
 * @file im_text_disabled.h
 * @author FluxxCode (info.fluxxcode@gmail.com)
 * @brief Contains item 'ImTextDisabled'
 * @copyright Copyright (c) 2022 - 2023
 */

#include "items/imgui_wrapper_items/im_wrapper_item_base.h"

#include "imgui.h"  // ImGuiMouseButton

namespace igm::internal
{

class ImTextDisabled : public ImWrapperItemBase
{
public:
    ImTextDisabled(std::string id, ItemBase* parent);

    void ImWrapperUpdate() noexcept;

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
};

}  // namespace igm::internal

#endif  // IMGUI_MARKUP_SRC_ITEMS_IMGUI_WRAPPER_ITEMS_IM_TEXT_DISABLED_H_
