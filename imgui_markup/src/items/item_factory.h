#ifndef IMGUI_MARKUP_SRC_ITEMS_ITEM_FACTORY_H_
#define IMGUI_MARKUP_SRC_ITEMS_ITEM_FACTORY_H_

/**
 * @file item_factory.h
 * @author FluxxCode (info.fluxxcode@gmail.com)
 * @brief Contains class to create items from strings.
 * @copyright Copyright (c) 2022
 */

#include "items/item_base.h"

// Widgets
#include "items/widgets/panel.h"
#include "items/widgets/button.h"
#include "items/widgets/text.h"

// Other
#include "items/other/container.h"
#include "items/other/internal_test.h"

#include <string>  // std::string
#include <memory>  // std::unique_ptr
#include <map>     // std::map

namespace igm::internal
{

/**
 * Singleton class to create specific items through strings.
 * Sets the mapping of item types within the markup language.
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
            // Widgets
            { "Panel", CreateItemInstance<Panel> },
            { "Button", CreateItemInstance<Button> },
            { "Text", CreateItemInstance<Text> },

            // Other
            { "Container", CreateItemInstance<Container> },
            { "_INTERNAL_TEST", CreateItemInstance<InternalTest> }
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

#endif  // IMGUI_MARKUP_SRC_ITEMS_ITEM_FACTORY_H_
