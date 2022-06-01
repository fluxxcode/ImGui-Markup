#ifndef IMGUI_MARKUP_SRC_ATTRIBUTE_TYPES_BASE_TYPES_ORIENTATION_H_
#define IMGUI_MARKUP_SRC_ATTRIBUTE_TYPES_BASE_TYPES_ORIENTATION_H_

/**
 * @file orientation.h
 * @author FluxxCode (info.fluxxcode@gmail.com)
 * @brief Contains custom orientation enum, used internally
 *        by the markup language.
 * @copyright Copyright (c) 2022
 */

namespace igm::internal::bt
{

enum class Orientation : unsigned char
{
    kHorizontal,
    kVertical
};

}  // namespace igm::internal::bt

#endif  // IMGUI_MARKUP_SRC_ATTRIBUTE_TYPES_BASE_TYPES_ORIENTATION_H_
