#ifndef IMGUI_MARKUP_SRC_ITEMS_OTHER_OTHER_BASE_H_
#define IMGUI_MARKUP_SRC_ITEMS_OTHER_OTHER_BASE_H_

/**
 * @file other_base.h
 * @author FluxxCode (info.fluxxcode@gmail.com)
 * @brief Contains base for every item not assigned to a specific category.
 * @copyright Copyright (c) 2022
 */

#include "items/item_base.h"

#include <vector>

namespace igm::internal
{

struct OtherBase : public ItemBase
{
    OtherBase(ItemType type, std::string id, ItemBase* parent)
        : ItemBase(type, ItemCategory::kOther, id, parent)
    { }

    OtherBase(const OtherBase&) = delete;
};

}  // namespace igm::internal

#endif  // IMGUI_MARKUP_SRC_ITEMS_OTHER_OTHER_BASE_H_
