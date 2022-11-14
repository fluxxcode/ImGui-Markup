#ifndef IMGUI_MARKUP_SRC_COMMON_UNITS_UNIT_TYPES_H_
#define IMGUI_MARKUP_SRC_COMMON_UNITS_UNIT_TYPES_H_

/**
 * @file unit_types.h
 * @author FluxxCode (info.fluxxcode@gmail.com)
 * @brief Contains enum for every unit type.
 * @copyright Copyright (c) 2022
 */

namespace igm::internal
{

enum class UnitType : unsigned char
{
    kGUI
};

std::string UnitTypeToString(UnitType type);

}  // namespace igm::internal

#endif  // IMGUI_MARKUP_SRC_COMMON_UNITS_UNIT_TYPES_H_
