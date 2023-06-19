#ifndef IMGUI_MARKUP_SRC_ITEMS_IMGUI_WRAPPER_ITEMS_IM_SPACING_H_
#define IMGUI_MARKUP_SRC_ITEMS_IMGUI_WRAPPER_ITEMS_IM_SPACING_H_

/**
 * @file im_spacing.h
 * @author FluxxCode (info.fluxxcode@gmail.com)
 * @brief Contains item 'ImSpacing'
 * @copyright Copyright (c) 2022 - 2023
 */

#include "items/imgui_wrapper_items/im_wrapper_item_base.h"

#include "imgui.h"  // ImGuiMouseButton

namespace igm::internal
{

class ImSpacing : public ImWrapperItemBase
{
public:
    ImSpacing(std::string id, ItemBase* parent);

    void ImWrapperUpdate() noexcept;

private:
    bt::Vector2 position_;

    bt::Vector2 GetSize() const noexcept { return bt::Vector2(); };
    bt::Vector2 GetPosition() const noexcept { return this->position_; };
};

}  // namespace igm::internal

#endif  // IMGUI_MARKUP_SRC_ITEMS_IMGUI_WRAPPER_ITEMS_IM_SPACING_H_
