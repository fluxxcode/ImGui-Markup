#include "impch.h"
#include "items/item_base.h"

/**
 * @file item_base.cpp
 * @author FluxxCode (info.fluxxcode@gmail.com)
 * @brief Implementation of item_base.h
 * @copyright Copyright (c) 2022
 */

#include "items/item_factory.h"

namespace igm::internal
{

ItemBase::ItemBase(ItemType type, ItemCategory category,
                   std::vector<UnitType> unit_types, std::string id,
                   ItemBase* parent)
    : type_(type), category_(category), unit_types_(unit_types), access_id_(id),
      parent_(parent)
{
    const void* address = static_cast<const void*>(this);
    std::stringstream ss;
    ss << address;
    this->unique_id_ = ss.str();
}

ItemBase* ItemBase::CreateChildItem(std::string type, std::string id) noexcept
{
    this->child_items_.push_back(ItemFactory::CreateItem(type, id, this));

    if (this->child_items_.back() == nullptr)
    {
        this->child_items_.pop_back();
        return nullptr;
    }

    return this->child_items_.back().get();
}

}  // namespace igm::internal

