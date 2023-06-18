#ifndef IMGUI_MARKUP_SRC_COMMON_UNITS_UNIT_BASE_H_
#define IMGUI_MARKUP_SRC_COMMON_UNITS_UNIT_BASE_H_

/**
 * @file unit.h
 * @author FluxxCode (info.fluxxcode@gmail.com)
 * @brief Contains base class for every unit type.
 * @copyright Copyright (c) 2023
 */

#include "items/item_base.h"

#include <vector>
#include <memory>

namespace igm::internal
{

/**
 * A unit contains the items of a loaded markup file or string.
 * Items are set by the interpreter.
 */
class Unit
{
public:
    Unit(const size_t unit_id);

    /**
     * Updates the entire item tree of the unit.
     */
    void Update(size_t display_width, size_t display_height) noexcept;

    /**
     * Applies the specified theme to every item currently in this unit.
    */
    void ApplyTheme(Theme& theme) noexcept;

    /**
     * Returns a list of all items IDs that match the given type.
     * Items without an ID are ignored.
    */
    std::vector<const char*> GetItemsOfType(ItemType type) const noexcept;

    /**
     * Returns the unit's ID.
     */
    inline size_t GetID() const noexcept { return this->unit_id_; }

    /**
     * Gets a reference to the unit's item tree.
     */
    inline std::vector<ItemBase*>& GetItemTree() noexcept
        { return this->item_tree_; }

    /**
     * Gets a reference to the unit's item mapping.
     * The item mapping contains the mapping of the item IDs to the items
     * themself.
     */
    inline std::map<std::string, ItemBase*>& GetItemMapping() noexcept
        { return this->item_id_mapping_; }

    /**
     * Clears the item tree and item mapping.
     */
    void Clear() noexcept;

protected:
    // Holds the main item tree within this unit
    std::vector<ItemBase*> item_tree_;

    // Contains mapping of the item ids to the item itself
    std::map<std::string, ItemBase*> item_id_mapping_;

    // Title of the root panel, currently the objects address
    std::string root_panel_title_;

    // The loaded theme of the unit
    ItemAccessManager theme_;

private:
    const size_t unit_id_;
};

}  // namespace igm::internal

#endif  // IMGUI_MARKUP_SRC_COMMON_UNITS_UNIT_BASE_H_
