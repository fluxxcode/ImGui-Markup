#ifndef IMGUI_MARKUP_SRC_ATTRIBUTE_TYPES_BASE_TYPES_VECTOR4_H_
#define IMGUI_MARKUP_SRC_ATTRIBUTE_TYPES_BASE_TYPES_VECTOR4_H_

/**
 * @file vector4.h
 * @author FluxxCode (info.fluxxcode@gmail.com)
 * @brief Contains custom vector4 using internal attribute types.
 *        Used internally by the markup language.
 * @copyright Copyright (c) 2022
 */

#include "attribute_types/float_wrapper.h"

namespace igm::internal::bt
{

struct Vector4
{
    Vector4()
        : x(0), y(0), z(0), w(0)
    { }
    Vector4(FloatWrapper x, FloatWrapper y, FloatWrapper z,
        FloatWrapper w)
        : x(x), y(y), z(z), w(w)
    { }

    FloatWrapper x;
    FloatWrapper y;
    FloatWrapper z;
    FloatWrapper w;
};

}  // namespace igm::internal::bt

#endif  // IMGUI_MARKUP_SRC_ATTRIBUTE_TYPES_BASE_TYPES_VECTOR4_H_
