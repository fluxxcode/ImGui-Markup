#ifndef IMGUI_MARKUP_SRC_ATTRIBUTE_TYPES_BASE_TYPES_COLOR_H_
#define IMGUI_MARKUP_SRC_ATTRIBUTE_TYPES_BASE_TYPES_COLOR_H_

/**
 * @file color.h
 * @author FluxxCode (info.fluxxcode@gmail.com)
 * @brief Contains custom color class used within the color_wrapper
 *        as main storage and reference.
 * @copyright Copyright (c) 2022
 */

#include "attribute_types/float_wrapper.h"

namespace igm::internal::bt
{

struct Color
{
    Color()
        : r(0), g(0), b(0), a(0)
    { }

    Color(float r, float g, float b, float a)
        : r(r), g(g), b(b), a(a)
    { }

    Color(FloatWrapper r, FloatWrapper g, FloatWrapper b,
          FloatWrapper a)
        : r(r), g(g), b(b), a(a)
    { }

    FloatWrapper r;
    FloatWrapper g;
    FloatWrapper b;
    FloatWrapper a;
};

}  // namespace igm::internal::bt

#endif  // IMGUI_MARKUP_SRC_ATTRIBUTE_TYPES_BASE_TYPES_COLOR_H_
