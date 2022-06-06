#ifndef IMGUI_MARKUP_SRC_ITEM_ITEM_MAPPING_H_
#define IMGUI_MARKUP_SRC_ITEM_ITEM_MAPPING_H_

/**
 * @file item_types.h
 * @author FluxxCode (info.fluxxcode@gmail.com)
 * @brief Contains enums for every item category and item type.
 * @copyright Copyright (c) 2022
 */

namespace igm::internal
{

enum class ItemCategory : unsigned char
{
    kWidget,
    kView,
    kOther
};

enum class ItemType : unsigned char
{
    // Widgets
    kPanel,
    kButton,

    // Other
    kInternalTest
};

}  // namespace igm::internal

#endif  // IMGUI_MARKUP_SRC_ITEM_ITEM_MAPPING_H_
