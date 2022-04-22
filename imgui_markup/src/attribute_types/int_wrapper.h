#ifndef IMGUI_MARKUP_SRC_ATTRIBUTE_TYPES_INT_WRAPPER_H_
#define IMGUI_MARKUP_SRC_ATTRIBUTE_TYPES_INT_WRAPPER_H_

/**
 * @file int_wrapper.h
 * @author FluxxCode (info.fluxxcode@gmail.com)
 * @brief Contains wrapper above the build-in type int.
 *        Used internally by the markup language.
 * @copyright Copyright (c) 2022
 */

#include "attribute_types/attribute_base.h"

namespace igm::internal
{

class IntWrapper : public AttributeBase<int>
{
public:
    IntWrapper()
        : AttributeBase(AttributeType::kInt, 0)
    { }

    IntWrapper(int value)
        : AttributeBase(AttributeType::kInt, value)
    { }

    inline operator int() { return this->GetValue(); }

    inline std::string ToString() noexcept
    {
        return std::to_string(this->GetValue());
    }

private:
    bool LoadValue(std::string value) noexcept;
    bool LoadValue(int value) noexcept;
    bool LoadValue(float value) noexcept;

    bool InitReference(IntWrapper& ref) noexcept;
};

}  // namespace igm::internal

#endif  // IMGUI_MARKUP_SRC_ATTRIBUTE_TYPES_INT_WRAPPER_H_
