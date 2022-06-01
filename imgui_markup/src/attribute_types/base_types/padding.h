#ifndef IMGUI_MARKUP_SRC_ATTRIBUTE_TYPES_BASE_TYPES_PADDING_H_
#define IMGUI_MARKUP_SRC_ATTRIBUTE_TYPES_BASE_TYPES_PADDING_H_

/**
 * @file padding.h
 * @author FluxxCode (info.fluxxcode@gmail.com)
 * @brief Contains custom padding class used within the padding_wrapper
 *        as main storage and reference.
 * @copyright Copyright (c) 2022
 */

#include "attribute_types/float_wrapper.h"

namespace igm::internal::bt
{

struct Padding
{
    Padding()
        : top(0), right(0), bottom(0), left(0)
    { }

    Padding(float top, float right, float bottom, float left)
        : top(top), right(right), bottom(bottom), left(left)
    { }

    Padding(FloatWrapper top, FloatWrapper right, FloatWrapper bottom,
            FloatWrapper left)
        : top(top), right(right), bottom(bottom), left(left)
    { }

    FloatWrapper top;
    FloatWrapper right;
    FloatWrapper bottom;
    FloatWrapper left;
};

}  // namespace igm::internal::bt

#endif  // IMGUI_MARKUP_SRC_ATTRIBUTE_TYPES_BASE_TYPES_PADDING_H_
