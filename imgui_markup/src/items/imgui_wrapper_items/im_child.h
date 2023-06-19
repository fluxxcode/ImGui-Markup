#ifndef IMGUI_MARKUP_SRC_ITEMS_IMGUI_WRAPPER_ITEMS_IM_CHILD_H_
#define IMGUI_MARKUP_SRC_ITEMS_IMGUI_WRAPPER_ITEMS_IM_CHILD_H_

/**
 * @file im_child.h
 * @author FluxxCode (info.fluxxcode@gmail.com)
 * @brief Contains item 'ImChild'
 * @copyright Copyright (c) 2022 - 2023
 */

#include "items/imgui_wrapper_items/im_wrapper_item_base.h"

#include "imgui.h"  // ImGuiMouseButton

namespace igm::internal
{

class ImChild : public ItemBase
{
public:
    ImChild(std::string id, ItemBase* parent);

    void ItemUpdate(bt::Vector2 position, bt::Vector2 available_size,
                    bool dynamic_w, bool dynamic_h) noexcept;

private:
    StringWrapper id_;
    Vector2Wrapper size_overwrite_ = Vector2Wrapper(0.0f, 0.0f);
    BoolWrapper border_ = BoolWrapper(false);

    bt::Vector2 position_;
    bt::Vector2 size_;

    bool is_hovered_ = false;

    bt::Vector2 GetSize() const noexcept { return this->size_; };
    bt::Vector2 GetPosition() const noexcept { return this->position_; };

    // API functions
    bool API_IsItemPressed(ImGuiMouseButton btn) noexcept;
    bool API_IsItemHovered() noexcept;

    // See item_base.h for more information
    virtual bool OnProcessEnd(std::string& error_message) noexcept;
};
}  // namespace igm::internal

#endif  // IMGUI_MARKUP_SRC_ITEMS_IMGUI_WRAPPER_ITEMS_IM_CHILD_H_
