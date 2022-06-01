#ifndef IMGUI_MARKUP_SRC_ITEM_WIDGETS_PANEL_H_
#define IMGUI_MARKUP_SRC_ITEM_WIDGETS_PANEL_H_

/**
 * @file panel.h
 * @author FluxxCode (info.fluxxcode@gmail.com)
 * @brief Header for the item 'Panel'
 * @copyright Copyright (c) 2022
 */

#include "items/widgets/widget_base.h"

#include <string>  // std::string

namespace igm::internal
{

// NOTE: The panel is currently only used for testing purposes.
struct Panel : public WidgetBase
{
    Panel(std::string id, ItemBase* parent);

    IntWrapper int_value_;
    FloatWrapper float_value_;
    BoolWrapper bool_value_;
    StringWrapper string_value_;
    Vector2Wrapper vec2_value_;
    Vector4Wrapper vec4_value_;
    PaddingWrapper padding_value_;
    MarginWrapper margin_value_;
    OrientationWrapper orientation_value_ = bt::Orientation::kHorizontal;

    void API_Update() noexcept;
};

}  // namespace igm::internal

#endif  // IMGUI_MARKUP_SRC_ITEM_WIDGETS_PANEL_H_
