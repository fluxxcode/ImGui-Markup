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

/**
 * Class used to access a specific item.
 * The class is there so that when items are deleted, they no longer
 * have any further references.
*/
class ItemAccessManager
{
public:
    ItemAccessManager();
    virtual ~ItemAccessManager();

    /**
     * References a new item to be able to access it.
     * Registers with the item as access manager, so the Clear()
     * method is called when the referenced item is deleted.
    */
    void TrackItem(ItemBase& item) noexcept;

    /**
     * Detaches itself from the referenced item and dereferences the item,
     * (sets item_ to nullptr)
    */
    void Clear() noexcept;

    /**
     * Returns the currently referenced item.
     * If no item is currently referenced or the item being referenced
     * is deleted, nullptr is returned.
    */
    inline ItemBase* GetItem() const noexcept
        { return this->item_; }

private:
    ItemBase* item_ = nullptr;
};

}  // namespace igm::internal

#endif  // IMGUI_MARKUP_SRC_ITEMS_ITEM_ACCESS_MANAGER_H_
