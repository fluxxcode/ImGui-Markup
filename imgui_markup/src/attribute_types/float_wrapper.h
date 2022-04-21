#ifndef IMGUI_MARKUP_SRC_ATTRIBUTE_TYPES_FLOAT_WRAPPER_H_
#define IMGUI_MARKUP_SRC_ATTRIBUTE_TYPES_FLOAT_WRAPPER_H_

#include "attribute_types/attribute_types.h"

namespace igm::internal
{

class FloatWrapper : public AttributeBase<float>
{
public:
    FloatWrapper()
        : AttributeBase(AttributeType::kFloat, 0.0f)
    { }

    FloatWrapper(float value)
        : AttributeBase(AttributeType::kFloat, value)
    { }

    operator float() { return this->GetValue(); }

    inline std::string ToString() noexcept
    {
        return std::to_string(this->GetValue());
    }

private:
    bool LoadValue(std::string value) noexcept;
    bool LoadValue(float value) noexcept;
    bool LoadValue(int value) noexcept;

    bool InitReference(FloatWrapper& ref) noexcept;
};

}  // namespace igm::internal

#endif  // IMGUI_MARKUP_SRC_ATTRIBUTE_TYPES_FLOAT_WRAPPER_H_
