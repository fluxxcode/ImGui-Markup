#include "impch.h"
#include "items/item_base.h"

#include "items/item_factory.h"

namespace igm::internal
{

ItemBase::ItemBase(ItemType type, ItemCategory category, std::string id,
                   ItemBase* parent)
    : type_(type), category_(category), access_id_(id), parent_(parent)
{
    const void* address = static_cast<const void*>(this);
    std::stringstream ss;
    ss << address;
    this->unique_id_ = ss.str();
}

ItemBase* ItemBase::CreateChildItem(std::string type, std::string id)
{
    this->child_items_.push_back(ItemFactory::CreateItem(type, id, this));

    if (this->child_items_.back() == nullptr)
    {
        this->child_items_.pop_back();
        return nullptr;
    }

    return this->child_items_.back().get();
}

void ItemBase::SetAttribute(std::string name, std::string value)
{
    // TODO: Proper implementation when attributes are implemented
    this->attributes_["name"] = value;
}

}  // namespace igm::internal

