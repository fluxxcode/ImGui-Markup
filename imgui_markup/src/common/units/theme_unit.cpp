#include "impch.h"
#include "common/units/theme_unit.h"

/**
 * @file theme_unit.cpp
 * @author FluxxCode (info.fluxxcode@gmail.com)
 * @brief Implementation of theme_unit.h
 * @copyright Copyright (c) 2022
 */

namespace igm::internal
{

ThemeUnit::ThemeUnit(const size_t unit_id)
    : UnitBase(unit_id, UnitType::kTheme)
{ }

}  // namespace igm::internal
