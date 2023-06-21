#ifndef IMGUI_MARKUP_SRC_ATTRIBUTE_TYPES_BASE_TYPES_DIRECTION_H_
#define IMGUI_MARKUP_SRC_ATTRIBUTE_TYPES_BASE_TYPES_DIRECTION_H_

/**
 * @file direction.h
 * @author FluxxCode (info.fluxxcode@gmail.com)
 * @brief Contains custom direction enum
 * @copyright Copyright (c) 2022 - 2023
 */

namespace igm::internal::bt
{

enum class Direction : unsigned char
{
    kLeft = 0,
    kRight = 1,
    kUp = 2,
    kDown = 3
};

}  // namespace igm::internal::bt

#endif  // IMGUI_MARKUP_SRC_ATTRIBUTE_TYPES_BASE_TYPES_DIRECTION_H_
