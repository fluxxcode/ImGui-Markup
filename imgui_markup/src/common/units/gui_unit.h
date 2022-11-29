#ifndef IMGUI_MARKUP_SRC_COMMON_UNITS_GUI_UNIT_H_
#define IMGUI_MARKUP_SRC_COMMON_UNITS_GUI_UNIT_H_

/**
 * @file gui_unit.h
 * @author FluxxCode (info.fluxxcode@gmail.com)
 * @brief Contains the unit type 'GUI'
 * @copyright Copyright (c) 2022
 */

#include "common/units/unit_base.h"
#include "items/item_access_manager.h"
#include "items/style/theme.h"

namespace igm::internal
{

class GUIUnit : public UnitBase
{
public:
    GUIUnit(const size_t unit_id);

    /**
     * Overwrites UnitBase::Update().
     * Creates a root panel and updates the item tree of the unit within
     * the newly created root panel.
     */
    void Update(size_t display_width, size_t display_height) noexcept;

    void ApplyTheme(Theme& theme) noexcept;

private:
    /*
     * Title of the root panel, currently the objects address.
    */
    std::string root_panel_title_;

    ItemAccessManager theme_;
};

}  // namespace igm::internal

#endif  // IMGUI_MARKUP_SRC_COMMON_UNITS_GUI_UNIT_H_
