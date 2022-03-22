#include "impch.h"
#include "imgui_markup.h"

#include "items/widgets/panel.h"
#include "items/item_factory.h"

namespace igm
{

void Print()
{
    internal::Panel panel("panel_0", nullptr);

    panel.SetAttribute("attribute_0", "value_0");

    internal::ItemBase* child_0 = panel.CreateChildItem("Panel", "panel_1");
    internal::ItemBase* child_1 = panel.CreateChildItem("Button", "button_0");

    panel.Update();
}

}  // namespace igm
