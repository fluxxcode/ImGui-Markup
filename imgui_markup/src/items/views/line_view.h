#ifndef IMGUI_MARKUP_SRC_ITEMS_VIEWS_LINE_VIEW_H_
#define IMGUI_MARKUP_SRC_ITEMS_VIEWS_LINE_VIEW_H_

/**
 * @file im_line_view.h
 * @author FluxxCode (info.fluxxcode@gmail.com)
 * @brief Contains item 'LineView'
 * @copyright Copyright (c) 2022
 */

#include "items/views/view_base.h"

#include "imgui.h"  // ImGuiMouseButton

#include <string>  // std::string

namespace igm::internal
{

struct LineView : public ViewBase
{
    LineView(std::string id, ItemBase* parent);

    void Update(bt::Vector2 position, bt::Vector2 size) noexcept;

    bool OnProcessStart(std::string& error_message) noexcept;
};

}  // namespace igm::internal

#endif  // IMGUI_MARKUP_SRC_ITEMS_VIEWS_LINE_VIEW_H_
