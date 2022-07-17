#ifndef IMGUI_MARKUP_SRC_ITEMS_WIDGETS_TEXT_H_
#define IMGUI_MARKUP_SRC_ITEMS_WIDGETS_TEXT_H_

/**
 * @file text.h
 * @author FluxxCode (info.fluxxcode@gmail.com)
 * @brief Contains item 'Text'
 * @copyright Copyright (c) 2022
 */

#include "items/widgets/widget_base.h"

#include "imgui.h"  // ImGuiMouseButton

#include <string>  // std::string

namespace igm::internal
{

class Text : public WidgetBase
{
public:
    Text(std::string id, ItemBase* parent);

    void WidgetUpdate(bt::Vector2 position, bt::Vector2 size) noexcept;

private:
    StringWrapper text_;

    // See widget_base.h for more information
    bt::Vector2 actual_size_;
    bool is_hovered_ = false;
    bool initialized_ = false;

    bt::Vector2 CalcItemSize() const noexcept;
    inline bool IsInitialized() const noexcept
        { return this->initialized_; }
    inline bt::Vector2 GetActualSize() const noexcept
        { return this->actual_size_; }

    // API functions
    bool API_IsItemPressed(ImGuiMouseButton btn) noexcept;
    bool API_IsItemHovered() noexcept;
};

}  // namespace igm::internal

#endif  // IMGUI_MARKUP_SRC_ITEMS_WIDGETS_TEXT_H_
