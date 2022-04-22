#ifndef IMGUI_MARKUP_SRC_ATTRIBUTE_TYPES_FLOAT_WRAPPER_H_
#define IMGUI_MARKUP_SRC_ATTRIBUTE_TYPES_FLOAT_WRAPPER_H_

/**
 * @file float_wrapper.h
 * @author FluxxCode (info.fluxxcode@gmail.com)
 * @brief Contains wrapper above the build-in type float.
 *        Used internally by the markup language.
 * @copyright Copyright (c) 2022
 */

#include "attribute_types/attribute_base.h"

namespace igm::internal
{

class FloatWrapper : public AttributeBase<float>
{
public:
    FloatWrapper()
        : AttributeBase(AttributeType::kFloat, 0.0f)
    { }

    explicit FloatWrapper(float value)
        : AttributeBase(AttributeType::kFloat, value)
    { }

    operator float() const { return this->GetValue(); }

    inline std::string ToString() const noexcept
    {
        return std::to_string(this->GetValue());
    }

private:
    bool LoadValue(const FloatWrapper& val) noexcept;
    bool LoadValue(const IntWrapper& val) noexcept;

    bool InitReference(FloatWrapper& ref) noexcept;
};

}  // namespace igm::internal

#endif  // IMGUI_MARKUP_SRC_ATTRIBUTE_TYPES_FLOAT_WRAPPER_H_
