#ifndef IMGUI_MARKUP_SRC_ITEMS_ITEM_LIST_H_
#define IMGUI_MARKUP_SRC_ITEMS_ITEM_LIST_H_

#include "items/item_base.h"

#include "items/widgets/panel.h"

namespace igm::internal
{

/**
 * Singleton class to create items by strings.
 */
class ItemFactory
{
public:
    ItemFactory(const ItemFactory&) = delete;
    void operator=(ItemFactory const&) = delete;

    static std::unique_ptr<ItemBase> CreateItem(
        std::string type, std::string access_id, ItemBase* parent
    ) noexcept;

private:
    const std::map<std::string, std::function<std::unique_ptr<ItemBase>(
        std::string, ItemBase*)>> item_mapping_ = {
            { "Panel", CreateItemInstance<Panel> }
        };

    ItemFactory() { };

    static ItemFactory& Get() noexcept;

    std::unique_ptr<ItemBase> IMPL_CreateItem(
        std::string type, std::string access_id, ItemBase* parent
    ) const noexcept;

    template<typename T>
    static std::unique_ptr<T> CreateItemInstance(
        std::string access_id, ItemBase* parent) noexcept
    {
        return std::make_unique<T>(access_id, parent);
    }
};

}  // namespace igm::internal

#endif  // IMGUI_MARKUP_SRC_ITEMS_ITEM_LIST_H_