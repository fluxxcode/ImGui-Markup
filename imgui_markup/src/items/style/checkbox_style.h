#ifndef IMGUI_MARKUP_SRC_ITEMS_STYLE_CHECKBOX_STYLE_H_
#define IMGUI_MARKUP_SRC_ITEMS_STYLE_CHECKBOX_STYLE_H_

/**
 * @file checkbox_style.h
 * @author FluxxCode (info.fluxxcode@gmail.com)
 * @brief Contains item 'CheckboxStyle'
 * @copyright Copyright (c) 2023
 */

#include "items/style/style_base.h"

namespace igm::internal
{

class CheckboxStyle : public StyleBase
{
public:
    CheckboxStyle(std::string id, ItemBase* parent);

    void PushStyle(ItemBase& item) const noexcept;
    void PopStyle() const noexcept;

private:
    Vector4Wrapper text_color_;
    Vector4Wrapper text_color_hovered_;
    Vector4Wrapper text_color_active_;
};

}  // namespace igm::internal

#endif  // IMGUI_MARKUP_SRC_ITEMS_STYLE_CHECKBOX_STYLE_H_
