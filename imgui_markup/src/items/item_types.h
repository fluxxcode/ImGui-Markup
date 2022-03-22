#ifndef IMGUI_MARKUP_SRC_ITEM_ITEM_MAPPING_H_
#define IMGUI_MARKUP_SRC_ITEM_ITEM_MAPPING_H_

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
    kPanel
};

}  // namespace igm::internal

#endif  // IMGUI_MARKUP_SRC_ITEM_ITEM_MAPPING_H_
