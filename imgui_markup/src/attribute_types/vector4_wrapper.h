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
        : AttributeBase(AttributeType::kVector4, InternalVector4(x, y, z, w))
    { }

    Vector4Wrapper(InternalVector4 value)
        : AttributeBase(AttributeType::kVector4, value)
    { }

    inline operator InternalVector4()
    {
        return this->GetValue();
    }

    inline std::string ToString() noexcept
    {
        InternalVector4& val = this->GetValue();
        return std::to_string(val.x) + "," +
               std::to_string(val.y) + "," +
               std::to_string(val.z) + "," +
               std::to_string(val.w);
    }

private:
    bool LoadValue(InternalVector4& value) noexcept;

    bool InitReference(Vector4Wrapper& ref) noexcept;
};

}  // namespace igm::internal

#endif  // IMGUI_MARKUP_SRC_ATTRIBUTE_TYPES_VECTOR4_WRAPPER_H_
