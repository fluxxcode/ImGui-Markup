#include "impch.h"
#include "items/item_factory.h"

namespace igm::internal
{

std::unique_ptr<ItemBase> ItemFactory::CreateItem(
    std::string type, std::string id, ItemBase* parent) noexcept
{
    return ItemFactory::Get().IMPL_CreateItem(type, id, parent);
}

ItemFactory& ItemFactory::Get() noexcept
{
    static ItemFactory instance;
    return instance;
}

std::unique_ptr<ItemBase> ItemFactory::IMPL_CreateItem(
    std::string type, std::string id, ItemBase* parent) const noexcept
{
    if (this->item_mapping_.find(type) == this->item_mapping_.end())
        return nullptr;

    return this->item_mapping_.at(type)(id, parent);
}

}  // namespace igm::internal
