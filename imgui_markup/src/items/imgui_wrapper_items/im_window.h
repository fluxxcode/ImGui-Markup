#ifndef IMGUI_MARKUP_SRC_ITEMS_IMGUI_WRAPPER_ITEMS_IM_WINDOW_H_
#define IMGUI_MARKUP_SRC_ITEMS_IMGUI_WRAPPER_ITEMS_IM_WINDOW_H_

/**
 * @file im_window.h
 * @author FluxxCode (info.fluxxcode@gmail.com)
 * @brief Contains item 'ImWindow'
 * @copyright Copyright (c) 2022 - 2023
 */

#include "items/item_base.h"

#include "imgui.h"  // ImGuiMouseButton

namespace igm::internal
{

class ImWindow : public ItemBase
{
public:
    ImWindow(std::string id, ItemBase* parent);

    void ItemUpdate(bt::Vector2 position, bt::Vector2 available_size,
                    bool dynamic_w, bool dynamic_h) noexcept;

private:
    bt::Vector2 position_;
    bt::Vector2 size_;

    StringWrapper name_;

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

#endif  // IMGUI_MARKUP_SRC_ITEMS_IMGUI_WRAPPER_ITEMS_IM_WINDOW_H_
