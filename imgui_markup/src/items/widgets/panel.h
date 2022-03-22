#ifndef IMGUI_MARKUP_SRC_ITEM_WIDGETS_PANEL_H_
#define IMGUI_MARKUP_SRC_ITEM_WIDGETS_PANEL_H_

#include "items/widgets/widget_base.h"

namespace igm::internal
{

struct Panel : public WidgetBase
{
    Panel(std::string id, ItemBase* parent)
        : WidgetBase(ItemType::kPanel, id, parent)
    { }

    void Update() noexcept;
};

}  // namespace igm::internal

#endif  // IMGUI_MARKUP_SRC_ITEM_WIDGETS_PANEL_H_
