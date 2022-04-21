#ifndef IMGUI_MARKUP_SRC_ATTRIBUTE_TYPES_BOOL_WRAPPER_H_
#define IMGUI_MARKUP_SRC_ATTRIBUTE_TYPES_BOOL_WRAPPER_H_

#include "attribute_types/attribute_types.h"

namespace igm::internal
{

class BoolWrapper : public AttributeBase<bool>
{
public:
    BoolWrapper()
        : AttributeBase(AttributeType::kBool, false)
    { }

    BoolWrapper(bool value)
        : AttributeBase(AttributeType::kBool, value)
    { }

    inline operator bool() { return this->GetValue(); }

    inline std::string ToString() noexcept
    {
        return std::to_string(this->GetValue());
    }

private:
    bool LoadValue(std::string value) noexcept;
    bool LoadValue(bool value) noexcept;

    bool InitReference(BoolWrapper& ref) noexcept;
};

}  // namespace igm::internal

#endif  // IMGUI_MARKUP_SRC_ATTRIBUTE_TYPES_BOOL_WRAPPER_H_
