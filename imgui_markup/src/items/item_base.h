#ifndef IMGUI_MARKUP_SRC_ITEMS_ITEM_BASE_H_
#define IMGUI_MARKUP_SRC_ITEMS_ITEM_BASE_H_

#include "items/item_api.h"
#include "items/item_types.h"

namespace igm::internal
{

class ItemBase : public ItemAPI
{
public:
    ItemBase(ItemType type, ItemCategory category, std::string id,
             ItemBase* parent = nullptr);

    ItemBase(const ItemBase&) = delete;

    virtual void Update() noexcept { };

    ItemBase* CreateChildItem(std::string type, std::string access_id);
    void SetAttribute(std::string name, std::string value);

protected:
    const ItemType type_;
    const ItemCategory category_;
    const std::string access_id_;  // ID to access the object via the API
                                   // or to reference the object through
                                   // the markup language
    std::string unique_id_;  // Address of the object, used as an unique ID.
    ItemBase* parent_;  // If nullptr, object is at the root of the tree
    std::vector<std::unique_ptr<ItemBase>> child_items_;

private:
    // TODO: Proper attribute implementation
    std::map<std::string, std::string> attributes_;
};

}  // namespace igm::internal

#endif  // IMGUI_MARKUP_SRC_ITEMS_ITEM_BASE_H_
