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

bool ItemBase::CreateAttribtue(std::string name, int value) noexcept
{
    if (this->IsAttributeDefined(name))
        return false;

    AttributeInterface* att = this->CreateDynamicAttribute<IntWrapper>(name);

    att->LoadValue(value);

    return true;
}

bool ItemBase::CreateAttribtue(std::string name, float value) noexcept
{
    if (this->IsAttributeDefined(name))
        return false;

    AttributeInterface* att = this->CreateDynamicAttribute<FloatWrapper>(name);

    att->LoadValue(value);

    return true;
}


bool ItemBase::CreateAttribtue(std::string name, bool value) noexcept
{
    if (this->IsAttributeDefined(name))
        return false;

    AttributeInterface* att = this->CreateDynamicAttribute<BoolWrapper>(name);

    att->LoadValue(value);

    return true;
}


bool ItemBase::CreateAttribtue(std::string name, const char* value) noexcept
{
    if (this->IsAttributeDefined(name))
        return false;

    AttributeInterface* att = this->CreateDynamicAttribute<StringWrapper>(name);

    att->LoadValue(value);

    return true;
}


bool ItemBase::CreateAttribtue(std::string name, Vector2 value) noexcept
{
    if (this->IsAttributeDefined(name))
        return false;

    AttributeInterface* att = this->CreateDynamicAttribute<Vector2Wrapper>(
        name);

    att->LoadValue(value);

    return true;
}


bool ItemBase::CreateAttribtue(std::string name, Vector4 value) noexcept
{
    if (this->IsAttributeDefined(name))
        return false;

    AttributeInterface* att = this->CreateDynamicAttribute<Vector4Wrapper>(
        name);

    att->LoadValue(value);

    return true;
}


}  // namespace igm::internal

