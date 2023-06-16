#ifndef IMGUI_MARKUP_SRC_ITEMS_STYLE_PANEL_STYLE_H_
#define IMGUI_MARKUP_SRC_ITEMS_STYLE_PANEL_STYLE_H_

/**
 * @file panel_style.h
 * @author FluxxCode (info.fluxxcode@gmail.com)
 * @brief Contains item 'PanelStyle'
 * @copyright Copyright (c) 2023
 */

#include "items/style/style_base.h"

namespace igm::internal
{

class PanelStyle : public StyleBase
{
public:
    PanelStyle(std::string id, ItemBase* parent);

    void PushStyle(ItemBase& item) const noexcept;
    void PopStyle() const noexcept;

private:
    Vector4Wrapper color_;
    Vector4Wrapper color_hovered_;
    Vector4Wrapper color_active_;
};

}  // namespace igm::internal

#endif  // IMGUI_MARKUP_SRC_ITEMS_STYLE_PANEL_STYLE_H_
