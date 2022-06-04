#ifndef IMGUI_MARKUP_SRC_ITEM_OTHER_INTERNAL_TEST_H_
#define IMGUI_MARKUP_SRC_ITEM_OTHER_INTERNAL_TEST_H_

/**
 * @file internal_test.h
 * @author FluxxCode (info.fluxxcode@gmail.com)
 * @brief Contains item only used for internal testing.
 * @copyright Copyright (c) 2022
 */

#include "items/other/other_base.h"

#include <string>  // std::string

namespace igm::internal
{

struct InternalTest : public OtherBase
{
    InternalTest(std::string id, ItemBase* parent);

    IntWrapper int_value_;
    FloatWrapper float_value_;
    BoolWrapper bool_value_;
    StringWrapper string_value_;
    Vector2Wrapper vec2_value_;
    Vector4Wrapper vec4_value_;
    PaddingWrapper padding_value_;
    MarginWrapper margin_value_;
    ColorWrapper color_value_;
    OrientationWrapper orientation_value_ = bt::Orientation::kHorizontal;

    void Update(bt::Vector2 position, bt::Vector2 size) noexcept;
};

}  // namespace igm::internal

#endif  // IMGUI_MARKUP_SRC_ITEM_OTHER_INTERNAL_TEST_H_
