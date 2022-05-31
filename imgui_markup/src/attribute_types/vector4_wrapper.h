#ifndef IMGUI_MARKUP_SRC_ATTRIBUTE_TYPES_VECTOR4_WRAPPER_H_
#define IMGUI_MARKUP_SRC_ATTRIBUTE_TYPES_VECTOR4_WRAPPER_H_

/**
 * @file vector4_wrapper.h
 * @author FluxxCode (info.fluxxcode@gmail.com)
 * @brief Contains wrapper above the internal vector4.
 *        Used internally by the markup language.
 * @copyright Copyright (c) 2022
 */

#include "attribute_types/internal/vector.h"
#include "attribute_types/attribute_base.h"

#include <string>  // std::string

namespace igm::internal
{

class Vector4Wrapper : public AttributeBase<at::Vector4>
{
public:
    Vector4Wrapper()
        : AttributeBase(AttributeType::kVector4, at::Vector4())
    { }

    Vector4Wrapper(float x, float y, float z, float w)
        : AttributeBase(AttributeType::kVector4,
                        at::Vector4((FloatWrapper)x, (FloatWrapper)y,
                                        (FloatWrapper)z, (FloatWrapper)w))
    { }

    Vector4Wrapper(at::Vector4 value)
        : AttributeBase(AttributeType::kVector4, value)
    { }

    inline operator at::Vector4() const
    {
        return this->GetValue();
    }

    inline std::string ToString() const noexcept
    {
        at::Vector4 val = this->GetValue();
        return val.x.ToString() + "," + val.y.ToString() + "," +
               val.z.ToString() + "," + val.w.ToString();
    }

private:
    bool LoadValue(const Vector4Wrapper& val) noexcept;

    bool InitReference(Vector4Wrapper& ref) noexcept;
};

}  // namespace igm::internal

#endif  // IMGUI_MARKUP_SRC_ATTRIBUTE_TYPES_VECTOR4_WRAPPER_H_
