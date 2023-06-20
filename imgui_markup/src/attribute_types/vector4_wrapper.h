#ifndef IMGUI_MARKUP_SRC_ATTRIBUTE_TYPES_VECTOR4_WRAPPER_H_
#define IMGUI_MARKUP_SRC_ATTRIBUTE_TYPES_VECTOR4_WRAPPER_H_

/**
 * @file vector4_wrapper.h
 * @author FluxxCode (info.fluxxcode@gmail.com)
 * @brief Contains wrapper above the internal vector4.
 *        Used internally by the markup language.
 * @copyright Copyright (c) 2022 - 2023
 */

#include "attribute_types/base_types/vector4.h"
#include "attribute_types/attribute_base.h"

#include <string>  // std::string

namespace igm::internal
{

class Vector4Wrapper : public AttributeBase<bt::Vector4>
{
public:
    Vector4Wrapper()
        : AttributeBase(AttributeType::kVector4, bt::Vector4())
    {
        this->Init();
    }

    Vector4Wrapper(float x, float y, float z, float w)
        : AttributeBase(AttributeType::kVector4,
                        bt::Vector4((FloatWrapper)x, (FloatWrapper)y,
                                    (FloatWrapper)z, (FloatWrapper)w))
    {
        this->Init();
    }

    Vector4Wrapper(bt::Vector4 value)
        : AttributeBase(AttributeType::kVector4, value)
    {
        this->Init();
    }

    Vector4Wrapper(ImVec4 value)
        : AttributeBase(AttributeType::kVector4, value)
    {
        this->Init();
    }

    inline void operator = (const Vector4Wrapper& val)
    {
        this->SetValue(val);
    }

    inline operator bt::Vector4() const { return this->Value(); }

    inline operator ImVec4() const
    {
        const bt::Vector4 val = this->Value();
        return ImVec4(val.x, val.y, val.z, val.w);
    }

    inline std::string GetName() const noexcept { return "Vector4"; }

    inline std::string ToString() const noexcept
    {
        bt::Vector4 val = this->Value();
        return val.x.ToString() + "," + val.y.ToString() + "," +
               val.z.ToString() + "," + val.w.ToString();
    }

private:
    void Init() noexcept;

    bool LoadValue(const Vector4Wrapper& val) noexcept;

    bool InitReference(Vector4Wrapper& ref) noexcept;
};

}  // namespace igm::internal

#endif  // IMGUI_MARKUP_SRC_ATTRIBUTE_TYPES_VECTOR4_WRAPPER_H_
