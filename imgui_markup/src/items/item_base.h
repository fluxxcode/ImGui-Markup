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
#include "attribute_types/internal_vector.h"

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

    virtual void Update() noexcept { };

    ItemBase* CreateChildItem(std::string type, std::string access_id) noexcept;

    bool CreateAttribtue(std::string name, int value) noexcept;
    bool CreateAttribtue(std::string name, float value) noexcept;
    bool CreateAttribtue(std::string name, bool value) noexcept;
    bool CreateAttribtue(std::string name, const char* value) noexcept;
    bool CreateAttribtue(std::string name, InternalVector2 value) noexcept;
    bool CreateAttribtue(std::string name, InternalVector4 value) noexcept;

    inline AttributeInterface* GetAttribute(std::string name) const noexcept
    {
        if (!this->IsAttributeDefined(name))
            return nullptr;

        return this->attributes_.at(name);
    }

    // Expecting type specified in items/attribute_types.h
    template<typename T>
    inline bool SetAttribute(std::string name, T value) noexcept
    {
        if (!this->IsAttributeDefined(name))
            return false;

        return this->attributes_.at(name)->LoadValue(value);
    }

    inline std::string GetAccessID() const noexcept
        { return this->access_id_; }

protected:
    const ItemType type_;
    const ItemCategory category_;
    const std::string access_id_;  // ID to access the object via the API
                                   // or to reference the object through
                                   // the markup language
    std::string unique_id_;  // Address of the object, used as an unique ID.
    ItemBase* parent_;  // If nullptr, object is at the root of the tree
    std::vector<std::unique_ptr<ItemBase>> child_items_;

    inline void AddAttribute(std::string name,
                             AttributeInterface* value) noexcept
    {
        this->attributes_[name] = value;
    }

    std::map<std::string, AttributeInterface*> attributes_;
private:
    // Main attributes set by the inheriting item

    // Expecting attribute wrapper defined in items/attribute_types.h
    template<typename T>
    AttributeInterface* CreateDynamicAttribute(std::string name) noexcept
    {
        static std::vector<T> dynamic_attributes;

        dynamic_attributes.emplace_back(T());

        AttributeInterface* interface =
            (AttributeInterface*)&dynamic_attributes.back();

        this->attributes_[name] = interface;

        return interface;
    }

    inline bool IsAttributeDefined(const std::string& name) const noexcept
    {
        if (this->attributes_.find(name) == this->attributes_.end())
            return false;

        return true;
    }
};

}  // namespace igm::internal

#endif  // IMGUI_MARKUP_SRC_ITEMS_ITEM_BASE_H_
