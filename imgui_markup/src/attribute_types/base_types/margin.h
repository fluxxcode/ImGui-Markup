#ifndef IMGUI_MARKUP_SRC_ATTRIBUTE_TYPES_BASE_TYPES_MARGIN_H_
#define IMGUI_MARKUP_SRC_ATTRIBUTE_TYPES_BASE_TYPES_MARGIN_H_

/**
 * @file margin.h
 * @author FluxxCode (info.fluxxcode@gmail.com)
 * @brief Contains custom margin class used within the margin_wrapper
 *        as main storage and reference.
 * @copyright Copyright (c) 2022
 */

#include "attribute_types/float_wrapper.h"

namespace igm::internal::bt
{

struct Margin
{
    Margin()
        : top(0), right(0), bottom(0), left(0)
    { }

    Margin(float top, float right, float bottom, float left)
        : top(top), right(right), bottom(bottom), left(left)
    { }

    Margin(FloatWrapper top, FloatWrapper right, FloatWrapper bottom,
           FloatWrapper left)
        : top(top), right(right), bottom(bottom), left(left)
    { }

    FloatWrapper top;
    FloatWrapper right;
    FloatWrapper bottom;
    FloatWrapper left;
};

}  // namespace igm::internal::bt

#endif  // IMGUI_MARKUP_SRC_ATTRIBUTE_TYPES_BASE_TYPES_MARGIN_H_
