#ifndef IMGUI_MARKUP_SRC_ITEMS_ITEM_ACCESS_MANAGER_H_
#define IMGUI_MARKUP_SRC_ITEMS_ITEM_ACCESS_MANAGER_H_

/**
 * @file item_access_manager.h
 * @author FluxxCode (info.fluxxcode@gmail.com)
 * @copyright Copyright (c) 2022
 */

#include "items/item_base.h"

namespace igm::internal
{

class ItemAccessManager
{
public:
    ItemAccessManager();
    virtual ~ItemAccessManager();

    inline void TrackItem(ItemBase& item) noexcept
    {
        if (this->item_)
            this->Clear();
        item.TrackItemAccessManager(*this);
        this->item_ = &item;
    }

    inline void Clear() noexcept
    {
        if (this->item_)
            this->item_->LoseItemAccessManager(*this);
        this->item_ = nullptr;
    };

    inline ItemBase* GetItem() const noexcept
        { return this->item_; }

private:
    ItemBase* item_ = nullptr;
};

}  // namespace igm::internal

#endif  // IMGUI_MARKUP_SRC_ITEMS_ITEM_ACCESS_MANAGER_H_
