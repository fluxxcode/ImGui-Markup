#ifndef IMGUI_MARKUP_SRC_ITEMS_ITEM_FACTORY_H_
#define IMGUI_MARKUP_SRC_ITEMS_ITEM_FACTORY_H_

/**
 * @file item_factory.h
 * @author FluxxCode (info.fluxxcode@gmail.com)
 * @brief Contains class to create items from strings.
 * @copyright Copyright (c) 2022 - 2023
 */

#include "imgui_markup_config.h"
#include "items/item_base.h"

// ImGui wrapper items
#include "items/imgui_wrapper_items/im_window.h"
#include "items/imgui_wrapper_items/im_text.h"
#include "items/imgui_wrapper_items/im_text_colored.h"
#include "items/imgui_wrapper_items/im_text_disabled.h"
#include "items/imgui_wrapper_items/im_text_wrapped.h"
#include "items/imgui_wrapper_items/im_label_text.h"
#include "items/imgui_wrapper_items/im_bullet_text.h"
#include "items/imgui_wrapper_items/im_button.h"
#include "items/imgui_wrapper_items/im_small_button.h"
#include "items/imgui_wrapper_items/im_arrow_button.h"
#include "items/imgui_wrapper_items/im_invisible_button.h"
#include "items/imgui_wrapper_items/im_radio_button.h"
#include "items/imgui_wrapper_items/im_radio_selection.h"
#include "items/imgui_wrapper_items/im_checkbox.h"
#include "items/imgui_wrapper_items/im_same_line.h"
#include "items/imgui_wrapper_items/im_group.h"
#include "items/imgui_wrapper_items/im_child.h"
#include "items/imgui_wrapper_items/im_separator.h"
#include "items/imgui_wrapper_items/im_spacing.h"
#include "items/imgui_wrapper_items/im_dummy.h"

// Other
#include "items/other/container.h"

#ifdef IMGUI_MARKUP_USE_EXPERIMENTAL

// Experimental
// Widgets
#include "items/gui/widgets/button.h"
#include "items/gui/widgets/text.h"
#include "items/gui/widgets/checkbox.h"

// Views
#include "items/gui/views/line_view.h"

// Styles
#include "items/style/theme.h"
#include "items/style/text_style.h"
#include "items/style/button_style.h"
#include "items/style/checkbox_style.h"
#include "items/style/panel_style.h"

// Other
#include "items/other/panel.h"
#include "items/other/internal_test.h"

#endif

#include <string>     // std::string
#include <memory>     // std::unique_ptr
#include <map>        // std::map
#include <functional> // std::function

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

    static ItemBase* CreateItem(
        std::string type, std::string access_id, ItemBase* parent
    ) noexcept;

private:
    const std::map<std::string, std::function<ItemBase*(
        std::string, ItemBase*)>> item_mapping_ = {
            // ImGui wrapper items
            { "ImWindow", CreateItemInstance<ImWindow> },
            { "ImText", CreateItemInstance<ImText> },
            { "ImTextColored", CreateItemInstance<ImTextColored> },
            { "ImTextDisabled", CreateItemInstance<ImTextDisabled> },
            { "ImTextWrapped", CreateItemInstance<ImTextWrapped> },
            { "ImLabelText", CreateItemInstance<ImLabelText> },
            { "ImBulletText", CreateItemInstance<ImBulletText> },
            { "ImButton", CreateItemInstance<ImButton> },
            { "ImSmallButton", CreateItemInstance<ImSmallButton> },
            { "ImInvisibleButton", CreateItemInstance<ImInvisibleButton> },
            { "ImArrowButton", CreateItemInstance<ImArrowButton> },
            { "ImRadioButton", CreateItemInstance<ImRadioButton> },
            { "ImRadioSelection", CreateItemInstance<ImRadioSelection> },
            { "ImCheckbox", CreateItemInstance<ImCheckbox> },
            { "ImSameLine", CreateItemInstance<ImSameLine> },
            { "ImGroup", CreateItemInstance<ImGroup> },
            { "ImChild", CreateItemInstance<ImChild> },
            { "ImSeparator", CreateItemInstance<ImSeparator> },
            { "ImSpacing", CreateItemInstance<ImSpacing> },
            { "ImDummy", CreateItemInstance<ImDummy> },

            // Other
            { "Container", CreateItemInstance<Container> },

            #ifdef IMGUI_MARKUP_USE_EXPERIMENTAL

            // Experimental
            // Widgets
            { "Button", CreateItemInstance<Button> },
            { "Text", CreateItemInstance<Text> },
            { "Checkbox", CreateItemInstance<Checkbox> },

            // Views
            { "LineView", CreateItemInstance<LineView> },

            // Styles
            { "Theme", CreateItemInstance<Theme> },
            { "TextStyle", CreateItemInstance<TextStyle> },
            { "ButtonStyle", CreateItemInstance<ButtonStyle> },
            { "CheckboxStyle", CreateItemInstance<CheckboxStyle> },
            { "PanelStyle", CreateItemInstance<PanelStyle> },

            // Other
            { "Panel", CreateItemInstance<Panel> },
            { "_INTERNAL_TEST", CreateItemInstance<InternalTest> }

            #endif
        };

    ItemFactory() { };

    static ItemFactory& Get() noexcept;

    ItemBase* IMPL_CreateItem(
        std::string type, std::string access_id, ItemBase* parent
    ) const noexcept;

    template<typename T>
    static T* CreateItemInstance(
        std::string access_id, ItemBase* parent) noexcept
    {
        return new T(access_id, parent);
    }
};

}  // namespace igm::internal

#endif  // IMGUI_MARKUP_SRC_ITEMS_ITEM_FACTORY_H_
