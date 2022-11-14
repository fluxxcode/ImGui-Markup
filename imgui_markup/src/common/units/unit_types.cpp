#include "impch.h"
#include "common/units/unit_types.h"

/**
 * @file unit_types.cpp
 * @author FluxxCode (info.fluxxcode@gmail.com)
 * @brief Implementation of unit_types.h
 * @copyright Copyright (c) 2022
 */

namespace igm::internal
{

std::string UnitTypeToString(UnitType type)
{
    switch (type)
    {
    case UnitType::kGUI: return "GUI";
    case UnitType::kTheme: return "Theme";
    }
    assert("Invalid unit type");
    return std::string();
}

}  // namespace igm::internal
