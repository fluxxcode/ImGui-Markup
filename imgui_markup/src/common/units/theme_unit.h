#ifndef IMGUI_MARKUP_SRC_COMMON_UNITS_THEME_UNIT_H_
#define IMGUI_MARKUP_SRC_COMMON_UNITS_THEME_UNIT_H_

/**
 * @file theme_unit.h
 * @author FluxxCode (info.fluxxcode@gmail.com)
 * @brief Contains the unit type 'Theme'
 * @copyright Copyright (c) 2022
 */

#include "common/units/unit_base.h"

#include <vector>

namespace igm::internal
{

/**
 * Unit used as a collection of multiple themes.
 */
struct ThemeUnit : public UnitBase
{
    ThemeUnit(const size_t unit_id);

    /**
     * Returns a list with the IDs of the loaded themes.
     * Themes without an ID are ignored.
    */
    std::vector<const char*> GetLoadedThemes() const noexcept;
};

}  // namespace igm::internal

#endif  // IMGUI_MARKUP_SRC_COMMON_UNITS_THEME_UNIT_H_
