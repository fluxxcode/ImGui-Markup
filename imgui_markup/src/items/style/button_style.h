#ifndef IMGUI_MARKUP_SRC_ITEMS_STYLE_BUTTON_STYLE_H_
#define IMGUI_MARKUP_SRC_ITEMS_STYLE_BUTTON_STYLE_H_

/**
 * @file button_style.h
 * @author FluxxCode (info.fluxxcode@gmail.com)
 * @brief Contains item 'ButtonStyle'
 * @copyright Copyright (c) 2023
 */

#include "items/style/style_base.h"

namespace igm::internal
{

class ButtonStyle : public StyleBase
{
public:
    ButtonStyle(std::string id, ItemBase* parent);

    void PushStyle(ItemBase& item) const noexcept;
    void PopStyle() const noexcept;

private:
    Vector4Wrapper color_;
    Vector4Wrapper color_hovered_;
    Vector4Wrapper color_active_;
    Vector4Wrapper text_color_;
    Vector4Wrapper text_color_hovered_;
    Vector4Wrapper text_color_active_;
};

}  // namespace igm::internal

#endif  // IMGUI_MARKUP_SRC_ITEMS_STYLE_BUTTON_STYLE_H_
