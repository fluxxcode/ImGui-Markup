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
        : AttributeBase(AttributeType::kVector2,
                        InternalVector2((FloatWrapper)x, (FloatWrapper)y))
    { }

    Vector2Wrapper(InternalVector2 value)
        : AttributeBase(AttributeType::kVector2, value)
    { }

    inline operator InternalVector2() const
    {
        return this->GetValue();
    }

    inline std::string ToString() const noexcept
    {
        InternalVector2 val = this->GetValue();
        return val.x.ToString() + "," + val.y.ToString();
    }

private:
    bool LoadValue(const Vector2Wrapper& val) noexcept;

    bool InitReference(Vector2Wrapper& ref) noexcept;
};

}  // namespace igm::internal

#endif  // IMGUI_MARUP_SRC_ATTRIBUTE_TYPES_VECTOR2_WRAPPER_H_