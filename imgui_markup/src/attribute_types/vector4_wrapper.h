#ifndef IMGUI_MARKUP_SRC_ATTRIBUTE_TYPES_VECTOR4_WRAPPER_H_
#define IMGUI_MARKUP_SRC_ATTRIBUTE_TYPES_VECTOR4_WRAPPER_H_

/**
 * @file vector4_wrapper.h
 * @author FluxxCode (info.fluxxcode@gmail.com)
 * @brief Contains wrapper above the internal vector4.
 *        Used internally by the markup language.
 * @copyright Copyright (c) 2022
 */

#include "attribute_types/internal_vector.h"
#include "attribute_types/attribute_base.h"

namespace igm::internal
{

class Vector4Wrapper : public AttributeBase<InternalVector4>
{
public:
    Vector4Wrapper()
        : AttributeBase(AttributeType::kVector4, InternalVector4())
    { }

    Vector4Wrapper(float x, float y, float z, float w)
        : AttributeBase(AttributeType::kVector4,
                        InternalVector4((FloatWrapper)x, (FloatWrapper)y,
                                        (FloatWrapper)z, (FloatWrapper)w))
    { }

    Vector4Wrapper(InternalVector4 value)
        : AttributeBase(AttributeType::kVector4, value)
    { }

    inline operator InternalVector4() const
    {
        return this->GetValue();
    }

    inline std::string ToString() const noexcept
    {
        InternalVector4 val = this->GetValue();
        return val.x.ToString() + "," + val.y.ToString() + "," +
               val.z.ToString() + "," + val.w.ToString();
    }

private:
    bool LoadValue(const Vector4Wrapper& val) noexcept;

    bool InitReference(Vector4Wrapper& ref) noexcept;
};

}  // namespace igm::internal

#endif  // IMGUI_MARKUP_SRC_ATTRIBUTE_TYPES_VECTOR4_WRAPPER_H_
