#ifndef IMGUI_MARKUP_SRC_ITEMS_IMGUI_WRAPPER_ITEMS_IM_WRAPPER_ITEM_BASE_H_
#define IMGUI_MARKUP_SRC_ITEMS_IMGUI_WRAPPER_ITEMS_IM_WRAPPER_ITEM_BASE_H_

/**
 * @file im_wrapper_item_base.h
 * @author FluxxCode (info.fluxxcode@gmail.com)
 * @brief Contains the base class 'ImWrapperItemBase'
 * @copyright Copyright (c) 2022 - 2023
 */

#include "items/item_base.h"

namespace igm::internal
{

class ImWrapperItemBase : public ItemBase
{
public:
    ImWrapperItemBase(ItemType type, std::string id, ItemBase* parent);

    // NOTE: The basic ImGui wrapper items ignore the function parameters
    virtual void ItemUpdate(bt::Vector2 position, bt::Vector2 available_size,
                            bool dynamic_w, bool dynamic_h) noexcept;

private:
    virtual void ImWrapperUpdate() noexcept = 0;
};

}  // namespace igm::internal

#endif  // IMGUI_MARKUP_SRC_ITEMS_IMGUI_WRAPPER_ITEMS_IM_WRAPPER_ITEM_BASE_H_
