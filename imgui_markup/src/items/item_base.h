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
#include "attribute_types/attribute_base.h"
#include "attribute_types/internal/vector.h"

#include <string>  // std::string
#include <memory>  // std::unique_ptr
#include <map>     // std::map

namespace igm::internal
{

/**
 * Parent of every item within the markup language.
 * Implements functions related to every item, mostly attribute and
 * child handling.
 */
class ItemBase : public ItemAPI
{
public:
    ItemBase(ItemType type, ItemCategory category, std::string id,
             ItemBase* parent = nullptr);

    ItemBase(const ItemBase&) = delete;

    virtual void API_Update() noexcept { };

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
     *               the markup langauge.
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

    inline std::string GetAccessID() const noexcept
        { return this->access_id_; }

protected:
    const ItemType type_;
    const ItemCategory category_;

    /**
     * ID to access the object via the API or to reference the object
     * through the markup language.
     * NOTE: This is NOT the full ID!
     */
    const std::string access_id_;

    /**
     * Unique ID that equals the address of the object.
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
     * Adds an attribute to the attribute list with the curresponding
     * name used within the markup language.
     */
    inline void AddAttribute(std::string name,
                             AttributeInterface* value) noexcept
    {
        this->attribute_list_[name] = value;
    }

private:
    // Main attributes set by the inheriting item
    std::map<std::string, AttributeInterface*> attribute_list_;

    std::vector<std::unique_ptr<AttributeInterface>> dynamic_attributes_;

    inline bool IsAttributeDefined(const std::string& name) const noexcept
    {
        if (this->attribute_list_.find(name) == this->attribute_list_.end())
            return false;

        return true;
    }
};

}  // namespace igm::internal

#endif  // IMGUI_MARKUP_SRC_ITEMS_ITEM_BASE_H_
