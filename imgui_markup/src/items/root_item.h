#ifndef IMGUI_MARKUP_SRC_ITEMS_ROOT_ITEM_H_
#define IMGUI_MARKUP_SRC_ITEMS_ROOT_ITEM_H_

/**
 * @file root_item.h
 * @author FluxxCode (info.fluxxcode@gmail.com)
 * @brief Root item of every item tree.
 * @copyright Copyright (c) 2022 - 2023
 */

#include "items/item_base.h"

#include <vector>

namespace igm::internal
{

class RootItem
{
public:
    RootItem();

    /**
     * Updates every item of the item tree.
     */
    void Update(size_t display_width, size_t display_height) noexcept;

    /**
     * Clears the item tree and deletes every item.
     */
    void Clear() noexcept;

    /**
     * Pushes a new item to the item tree.
    */
    inline std::vector<std::unique_ptr<ItemBase>>& GetItemTree() noexcept
        { return this->item_tree_; };

private:
    std::vector<std::unique_ptr<ItemBase>> item_tree_;

    /*
     * Title of the root panel, currently the objects address.
    */
    std::string root_panel_title_;
};

}  // namespace igm::internal

#endif  // IMGUI_MARKUP_SRC_ITEMS_ROOT_ITEM_H_
