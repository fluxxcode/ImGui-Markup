#ifndef IMGUI_MARKUP_SRC_ITEMS_ITEM_BASE_H_
#define IMGUI_MARKUP_SRC_ITEMS_ITEM_BASE_H_

/**
 * @file item_base.h
 * @author FluxxCode (info.fluxxcode@gmail.com)
 * @brief Contains ItemBase, parent of every item within the markup language.
 * @copyright Copyright (c) 2022
 */

#include "items/item_api.h"
#include "items/item_types.h"
#include "common/units/unit_types.h"
#include "attribute_types/attribute_types.h"

#include <string>  // std::string
#include <memory>  // std::unique_ptr
#include <map>     // std::map


namespace igm::internal
{

class StyleBase;
class ItemAccessManager;

/**
 * Parent of every item within the markup language.
 * Implements functions related to every item, mostly attribute and
 * child handling.
 */
class ItemBase : public ItemAPI
{
public:
    /**
     * @param type - Type of the item
     * @param category - Category the item belongs to
     * @param units - Array of units in which the item can be placed.
     *                The item can be placed in every unit if the array
     *                is empty.
     * @param id - Access ID of the item.
     * @param parent - Pointer to the parent item. Can be nullptr
     *                 if the item is at the root of the item tree.
     */
    ItemBase(ItemType type, ItemCategory category,
             std::vector<UnitType> unit_types, std::string id,
             ItemBase* parent = nullptr);
    virtual ~ItemBase();
    ItemBase(const ItemBase&) = delete;

    /**
     * Main update function of the item.
     * This is only a wrapper for the ItemUpdate function,
     * used to push and pop style items.
     *
     * @param position - The ImGui position of the item, relative to the
     *                   next parent window.
     * @param available_size - Available size for the item.
     * @param dynamic_w - Sets whether the available width can be ignored.
     * @param dynamic_h - Sets whether the available height can be ignored.
     */
    void Update(bt::Vector2 position, bt::Vector2 available_size,
                bool dynamic_w, bool dynamic_h) noexcept;

    /**
     * Default implementation of API_Update.
     * Currently only calls the Update function with both
     * dynamic_w and dynamic_h disabled.
     */
    virtual void API_Update(bt::Vector2 position, bt::Vector2 size) noexcept;

    ItemBase* CreateChildItem(std::string type, std::string access_id) noexcept;

    inline AttributeInterface* GetAttribute(std::string name) const noexcept
    {
        if (!this->IsAttributeDefined(name))
            return nullptr;

        return this->attribute_list_.at(name);
    }

    /**
     * Copies the given attribute and adds it to the attribute list.
     *
     * @tparam T - Expecting an attribute wrapper defined in the
     *             directory attribute_types.
     * @param name - Name of the attribute to allow access from
     *               the markup language.
     * @param attribute - The attribute itself that will be copied and
     *                    added to the attribute list.
     *
     * @return true on success, false if there is already an attribute defined
     *         with the same name.
     */
    template<typename T>
    bool CreateAttribute(std::string name) noexcept
    {
        if (this->IsAttributeDefined(name))
            return false;

        this->dynamic_attributes_.push_back(std::make_unique<T>());
        this->attribute_list_[name] = this->dynamic_attributes_.back().get();

        return true;
    }

    /**
     * Pushes a new style to the style stack.
     */
    void InitStyle(StyleBase& style) noexcept;

    void TrackItemAccessManager(ItemAccessManager& item) noexcept;
    void LoseItemAccessManager(ItemAccessManager& item) noexcept;

    inline std::string GetAccessID() const noexcept
        { return this->access_id_; }

    inline ItemType GetType() const noexcept { return this->type_; }
    inline ItemCategory GetCategory() const noexcept { return this->category_; }
    inline std::vector<UnitType> GetUnitTypes() const noexcept
        { return this->unit_types_; }
    inline const ItemBase* GetParent() const noexcept { return this->parent_; }

    virtual bt::Vector2 GetSize() const noexcept { return bt::Vector2(); }
    virtual bt::Vector2 GetPosition() const noexcept { return bt::Vector2(); }

    /**
     * Function that is called by the interpreter before the interpreter
     * starts the process of the items child nodes.
     * Used to check for various errors.
     *
     * @param[in] error_message - String that will be set to the error message
     *                            if there is one.
     * @return true on success, false if there was an error.
     */
    virtual bool OnProcessStart(std::string& error_message) noexcept
        { return true; }

    /**
     * Function that is called by the interpreter after the interpreter
     * processed the child items and the item itself.
     * Used to check for various errors.
     *
     * @param[in] error_message - String that will be set to the error message
     *                            if there is one.
     * @return true on success, false if there was an error.
     */
    virtual bool OnProcessEnd(std::string& error_message) noexcept
        { return true; }

protected:
    /**
     * Type of the item.
     */
    const ItemType type_;

    /**
     * Category the item belongs to.
     */
    const ItemCategory category_;

    /**
     * Array of units in which the item can be placed.
     */
    const std::vector<UnitType> unit_types_;

    /**
     * Full ID to access the object via the API or to reference the object
     * through the markup language.
     */
    const std::string access_id_;

    /**
     * Unique ID that is equal to the address of the object.
     * Set within the constructor.
     */
    std::string unique_id_;

    /**
     * Parent item, nullptr if the item has no parent and is at the
     * root of the item tree.
     */
    ItemBase* parent_;

    std::vector<std::unique_ptr<ItemBase>> child_items_;

    /**
     * Function used by the inheriting item.
     * Adds an attribute to the attribute list with the corresponding
     * name used within the markup language.
     */
    inline void InitAttribute(std::string name,
                             AttributeInterface& value) noexcept
    {
        this->attribute_list_[name] = &value;
    }

private:
    // Main attributes set by the inheriting item
    std::map<std::string, AttributeInterface*> attribute_list_;

    std::vector<std::unique_ptr<AttributeInterface>> dynamic_attributes_;

    std::vector<ItemAccessManager*> tracked_access_manager_;

    /**
     * Stack of style items used to change the item's appearance.
     */
    std::vector<StyleBase*> style_items_;

    /**
     * Update function which should be implemented by the inheriting item.
     */
    virtual void ItemUpdate(bt::Vector2 position, bt::Vector2 available_size,
                            bool dynamic_w, bool dynamic_h) noexcept {};

    inline bool IsAttributeDefined(const std::string& name) const noexcept
    {
        if (this->attribute_list_.find(name) == this->attribute_list_.end())
            return false;

        return true;
    }
};

}  // namespace igm::internal

#endif  // IMGUI_MARKUP_SRC_ITEMS_ITEM_BASE_H_
