#ifndef IMGUI_MARKUP_SRC_ITEMS_IMGUI_WRAPPER_ITEMS_IM_TEXT_COLORED_H_
#define IMGUI_MARKUP_SRC_ITEMS_IMGUI_WRAPPER_ITEMS_IM_TEXT_COLORED_H_

/**
 * @file im_text_colored.h
 * @author FluxxCode (info.fluxxcode@gmail.com)
 * @brief Contains item 'ImTextColored'
 * @copyright Copyright (c) 2022 - 2023
 */

#include "items/imgui_wrapper_items/im_wrapper_item_base.h"

#include "imgui.h"  // ImGuiMouseButton

namespace igm::internal
{

class ImTextColored : public ImWrapperItemBase
{
public:
    ImTextColored(std::string id, ItemBase* parent);

    void ImWrapperUpdate() noexcept;

private:
    StringWrapper text_;
    Vector4Wrapper color_;

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

#endif  // IMGUI_MARKUP_SRC_ITEMS_IMGUI_WRAPPER_ITEMS_IM_TEXT_COLORED_H_
