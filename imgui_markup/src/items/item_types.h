#ifndef IMGUI_MARKUP_SRC_ITEMS_ITEM_TYPES_H_
#define IMGUI_MARKUP_SRC_ITEMS_ITEM_TYPES_H_

/**
 * @file item_types.h
 * @author FluxxCode (info.fluxxcode@gmail.com)
 * @brief Contains enums for every item category and item type.
 * @copyright Copyright (c) 2022 - 2023
 */

namespace igm::internal
{

enum class ItemCategory : unsigned char
{
    kImGuiWrapper,
    kWidget,
    kView,
    kStyle,
    kOther
};

enum class ItemType : unsigned char
{
    // Simple ImGui wrapper items
    kImWindow,
    kImText,
    kImButton,
    kImCheckbox,
    kImSameLine,
    kImGroup,
    kImChild,
    kImSeparator,

    // Experimental
    // Widgets
    kButton,
    kText,
    kCheckbox,

    // Views
    kLineView,

    // Style
    kTheme,
    kTextStyle,
    kButtonStyle,
    kCheckboxStyle,
    kPanelStyle,

    // Other
    kPanel,
    kContainer,
    kInternalTest
};

}  // namespace igm::internal

#endif  // IMGUI_MARKUP_SRC_ITEMS_ITEM_TYPES_H_
