#ifndef IMGUI_MARKUP_INCLUDE_IMGUI_MARKUP_H_
#define IMGUI_MARKUP_INCLUDE_IMGUI_MARKUP_H_

/**
 * @file imgui_markup.h
 * @author FluxxCode (info.fluxxcode@gmail.com)
 * @brief Header used for applications using the imgui_layer
 * @copyright Copyright (c) 2022
 */

#include "imgui_markup/types.h"
#include "imgui_markup/result.h"

namespace igm
{

/**
 * Parses a file as a GUI unit.
 *
 * @return ID of the created unit.
 */
size_t ParseFromFile(UnitType type, const char* path, bool* result = nullptr);

/**
 * Deletes all data related to a specific unit.
 */
void DeleteUnit(size_t unit, bool* result = nullptr);

/**
 * Get the last result of a specific unit.
 */
Result GetLastResult(size_t unit, bool* result = nullptr);

/**
 * Main function to update a specific unit and its childs.
 * Should be called every frame in which the unit is to be displayed.
 */
void Update(size_t unit, size_t display_width, size_t display_height,
            bool* result = nullptr);

/**
 * Main function to update a specific unit and its childs.
 * Should be called every frame in which the unit is to be displayed.
 * The display width and height will be set using ImGui.
 */
void Update(size_t unit, bool* result = nullptr);

bool InitUnitTheme(size_t dst_unit, size_t src_unit, const char* item,
                   bool* result = nullptr);

/************ ITEM API ************/

bool IsItemPressed(size_t unit, const char* item,
                   MouseButton mouse_button = MouseButton::kLeft,
                   bool* result = nullptr) noexcept;

bool IsItemHovered(size_t unit, const char* item,
                   bool* result = nullptr) noexcept;

bool IsCheckboxChecked(size_t unit, const char* item,
                       bool* result = nullptr) noexcept;

}  // namespace igm

#endif  // IMGUI_MARKUP_INCLUDE_IMGUI_MARKUP_H_
