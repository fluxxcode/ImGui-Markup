#ifndef IMGUI_MARKUP_SRC_ITEMS_STYLE_TEXT_STYLE_H_
#define IMGUI_MARKUP_SRC_ITEMS_STYLE_TEXT_STYLE_H_

/**
 * @file text_style.h
 * @author FluxxCode (info.fluxxcode@gmail.com)
 * @brief Contains item 'TextStyle'
 * @copyright Copyright (c) 2022
 */

#include "items/style/style_base.h"

namespace igm::internal
{

class TextStyle : public StyleBase
{
public:
    TextStyle(std::string id, ItemBase* parent);

    void PushStyle() const noexcept;
    void PopStyle() const noexcept;

private:
    Vector4Wrapper color_;
    Vector4Wrapper color_hovered_;
    Vector4Wrapper color_active_;
};

}  // namespace igm::internal

#endif  // IMGUI_MARKUP_SRC_ITEMS_STYLE_TEXT_STYLE_H_
