#ifndef IMGUI_MARKUP_SRC_ITEMS_GUI_VIEWS_LINE_VIEW_H_
#define IMGUI_MARKUP_SRC_ITEMS_GUI_VIEWS_LINE_VIEW_H_

/**
 * @file line_view.h
 * @author FluxxCode (info.fluxxcode@gmail.com)
 * @brief Contains item 'LineView'
 * @copyright Copyright (c) 2022
 */

#include "items/gui/views/view_base.h"

#include "imgui.h"  // ImGuiMouseButton

#include <string>  // std::string

namespace igm::internal
{

class LineView : public ViewBase
{
public:
    LineView(std::string id, ItemBase* parent);

    void ViewUpdate(bt::Vector2 position, bt::Vector2 size) noexcept;

private:
    PaddingWrapper padding_;
    IntWrapper spacing_;

    // See widget_base.h for more information
    bt::Vector2 actual_size_;
    bool initialized_ = false;

    bt::Vector2 CalcItemSize() const noexcept;
    inline bool IsInitialized() const noexcept
        { return this->initialized_; }
    inline bt::Vector2 GetActualSize() const noexcept
        { return this->actual_size_; }

};

}  // namespace igm::internal

#endif  // IMGUI_MARKUP_SRC_ITEMS_GUI_VIEWS_LINE_VIEW_H_
