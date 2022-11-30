#ifndef IMGUI_MARKUP_SRC_ITEMS_ITEM_ACCESS_MANAGER_H_
#define IMGUI_MARKUP_SRC_ITEMS_ITEM_ACCESS_MANAGER_H_

/**
 * @file item_access_manager.h
 * @author FluxxCode (info.fluxxcode@gmail.com)
 * @copyright Copyright (c) 2022
 */

namespace igm::internal
{

class ItemBase;

class ItemAccessManager
{
public:
    ItemAccessManager();
    virtual ~ItemAccessManager();

    void TrackItem(ItemBase& item) noexcept;
    void Clear() noexcept;
    inline ItemBase* GetItem() const noexcept
        { return this->item_; }

private:
    ItemBase* item_ = nullptr;
};

}  // namespace igm::internal

#endif  // IMGUI_MARKUP_SRC_ITEMS_ITEM_ACCESS_MANAGER_H_
