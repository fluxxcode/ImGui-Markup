#ifndef IMGUI_MARKUP_SRC_ITEMS_STYLE_BASE_H_
#define IMGUI_MARKUP_SRC_ITEMS_STYLE_BASE_H_

/**
 * @file style_base.h
 * @author FluxxCode (info.fluxxcode@gmail.com)
 * @brief Contains base for every style item.
 * @copyright Copyright (c) 2022
 */

#include "items/item_base.h"

namespace igm::internal
{

class StyleBase : public ItemBase
{
public:
    StyleBase(ItemType type, std::string id, ItemBase* parent,
              ItemType expected_parent);
    StyleBase(const StyleBase&) = delete;

    virtual void PushStyle(ItemBase& item) const noexcept = 0;
    virtual void PopStyle() const noexcept = 0;

    inline ItemType GetExpectedItem() const noexcept
        { return this->expected_item_; }

private:
    const ItemType expected_item_;

    // See item_base.h for more information
    bool OnProcessStart(std::string& error_message) noexcept;
};

}  // namespace igm::internal

#endif  // IMGUI_MARKUP_SRC_ITEMS_STYLE_BASE_H_
