#ifndef IMGUI_MARKUP_SRC_ATTRIBUTE_TYPES_INTERNAL_PADDING_H_
#define IMGUI_MARKUP_SRC_ATTRIBUTE_TYPES_INTERNAL_PADDING_H_

/**
 * @file padding.h
 * @author FluxxCode (info.fluxxcode@gmail.com)
 * @brief Contains custom padding class used within the padding_wrapper
 *        as main storage and reference.
 * @copyright Copyright (c) 2022
 */

#include "attribute_types/float_wrapper.h"

namespace igm::internal::at
{

struct Padding
{
    Padding()
        : top(0), right(0), bottom(0), left(0)
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

}  // namespace igm::internal::at

#endif  // IMGUI_MARKUP_SRC_ATTRIBUTE_TYPES_INTERNAL_PADDING_H_
