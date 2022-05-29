#ifndef IMGUI_MARKUP_SRC_ITEM_WIDGETS_PANEL_H_
#define IMGUI_MARKUP_SRC_ITEM_WIDGETS_PANEL_H_

/**
 * @file panel.h
 * @author FluxxCode (info.fluxxcode@gmail.com)
 * @brief Header for the item 'Panel'
 * @copyright Copyright (c) 2022
 */

#include "items/widgets/widget_base.h"

#include "attribute_types/bool_wrapper.h"
#include "attribute_types/int_wrapper.h"
#include "attribute_types/float_wrapper.h"
#include "attribute_types/string_wrapper.h"
#include "attribute_types/vector2_wrapper.h"
#include "attribute_types/vector4_wrapper.h"

#include <string>  // std::string

namespace igm::internal
{

// NOTE: The panel is currently only used for testing purposes.
struct Panel : public WidgetBase
{
    Panel(std::string id, ItemBase* parent);

    IntWrapper value_int_;
    FloatWrapper value_float_;
    BoolWrapper value_bool_;
    StringWrapper value_string_;
    Vector2Wrapper value_vec2_ = Vector2Wrapper();
    Vector4Wrapper value_vec4_ = Vector4Wrapper();

    void API_Update() noexcept;
};

}  // namespace igm::internal

#endif  // IMGUI_MARKUP_SRC_ITEM_WIDGETS_PANEL_H_
