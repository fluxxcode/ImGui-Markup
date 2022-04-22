#ifndef IMGUI_MARKUP_SRC_ATTRIBUTE_TYPES_VECTOR2_WRAPPER_H_
#define IMGUI_MARKUP_SRC_ATTRIBUTE_TYPES_VECTOR2_WRAPPER_H_

/**
 * @file vector2_wrapper.h
 * @author FluxxCode (info.fluxxcode@gmail.com)
 * @brief Contains wrapper above the internal vector2.
 *        Used internally by the markup language.
 * @copyright Copyright (c) 2022
 */

#include "attribute_types/internal_vector.h"
#include "attribute_types/attribute_base.h"

namespace igm::internal
{

class Vector2Wrapper : public AttributeBase<InternalVector2>
{
public:
    Vector2Wrapper()
        : AttributeBase(AttributeType::kVector2, InternalVector2())
    { }

    Vector2Wrapper(float x, float y)
        : AttributeBase(AttributeType::kVector2, InternalVector2(x, y))
    { }

    Vector2Wrapper(InternalVector2 value)
        : AttributeBase(AttributeType::kVector2, value)
    { }

    inline operator InternalVector2()
    {
        return this->GetValue();
    }

    inline std::string ToString() noexcept
    {
        InternalVector2& val = this->GetValue();
        return std::to_string(val.x) + "," +
               std::to_string(val.y);
    }

private:
    bool LoadValue(InternalVector2& value) noexcept;

    bool InitReference(Vector2Wrapper& ref) noexcept;
};

}  // namespace igm::internal

#endif  // IMGUI_MARUP_SRC_ATTRIBUTE_TYPES_VECTOR2_WRAPPER_H_
