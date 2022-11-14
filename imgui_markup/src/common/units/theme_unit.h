#ifndef IMGUI_MARKUP_SRC_COMMON_UNITS_THEME_UNIT_H_
#define IMGUI_MARKUP_SRC_COMMON_UNITS_THEME_UNIT_H_

/**
 * @file theme_unit.h
 * @author FluxxCode (info.fluxxcode@gmail.com)
 * @brief Contains the unit type 'Theme'
 * @copyright Copyright (c) 2022
 */

#include "common/units/unit_base.h"

namespace igm::internal
{

struct ThemeUnit : public UnitBase
{
    ThemeUnit(const size_t unit_id);

    /**
     * Overwrites UnitBase::Update().
     * Currently only updates the item tree.
     */
    void Update(size_t display_width, size_t display_height) noexcept;
};

}  // namespace igm::internal

#endif  // IMGUI_MARKUP_SRC_COMMON_UNITS_THEME_UNIT_H_
