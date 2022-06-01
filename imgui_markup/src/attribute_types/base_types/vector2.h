#ifndef IMGUI_MARKUP_SRC_ATTRIBUTE_TYPES_BASE_TYPES_VECTOR2_H_
#define IMGUI_MARKUP_SRC_ATTRIBUTE_TYPES_BASE_TYPES_VECTOR2_H_

/**
 * @file vector2.h
 * @author FluxxCode (info.fluxxcode@gmail.com)
 * @brief Contains custom vector2 using internal attribute types.
 *        Used internally by the markup language.
 * @copyright Copyright (c) 2022
 */

#include "attribute_types/float_wrapper.h"

namespace igm::internal::bt
{

struct Vector2
{
    Vector2()
        : x(0), y(0)
    { }
    Vector2(FloatWrapper x, FloatWrapper y)
        : x(x), y(y)
    { }

    FloatWrapper x;
    FloatWrapper y;
};

}  // namespace igm::internal::bt

#endif  // IMGUI_MARKUP_SRC_ATTRIBUTE_TYPES_BASE_TYPES_VECTOR2_H_
