#ifndef IMGUI_MARKUP_SRC_ATTRIBUTE_TYPES_INTERNAL_VECTOR_H_
#define IMGUI_MARKUP_SRC_ATTRIBUTE_TYPES_INTERNAL_VECTOR_H_

/**
 * @file vector.h
 * @author FluxxCode (info.fluxxcode@gmail.com)
 * @brief Contains custom vectors using the internal attribute types.
 *        Used internally by the markup language.
 * @copyright Copyright (c) 2022
 */

#include "attribute_types/float_wrapper.h"

namespace igm::internal::at
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

}  // namespace igm::internal::at

#endif  // IMGUI_MARKUP_SRC_ATTRIBUTE_TYPES_INTERNAL_VECTOR_H_
