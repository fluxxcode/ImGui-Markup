#ifndef IMGUI_MARKUP_SRC_ITEMS_IMGUI_WRAPPER_ITEMS_IM_SAME_LINE_H_
#define IMGUI_MARKUP_SRC_ITEMS_IMGUI_WRAPPER_ITEMS_IM_SAME_LINE_H_

/**
 * @file im_same_line.h
 * @author FluxxCode (info.fluxxcode@gmail.com)
 * @brief Contains item 'ImSameLine'
 * @copyright Copyright (c) 2022 - 2023
 */

#include "items/imgui_wrapper_items/im_wrapper_item_base.h"

#include "imgui.h"  // ImGuiMouseButton

namespace igm::internal
{

class ImSameLine : public ImWrapperItemBase
{
public:
    ImSameLine(std::string id, ItemBase* parent);

    void ImWrapperUpdate() noexcept;

private:
    bt::Vector2 position_;

    FloatWrapper offset_from_start_x_ = 0.0f;
    FloatWrapper spacing_ = -1.0f;

    bt::Vector2 GetPosition() const noexcept { return this->position_; };
};

}  // namespace igm::internal

#endif  // IMGUI_MARKUP_SRC_ITEMS_IMGUI_WRAPPER_ITEMS_IM_SAME_LINE_H_
