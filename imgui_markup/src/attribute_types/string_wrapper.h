#ifndef IMGUI_MARKUP_SRC_ATTRIBUTE_TYPES_STRING_WRAPPER_H_
#define IMGUI_MARKUP_SRC_ATTRIBUTE_TYPES_STRING_WRAPPER_H_

/**
 * @file string_wrapper.h
 * @author FluxxCode (info.fluxxcode@gmail.com)
 * @brief Contains wrapper above std::string.
 *        Used internally by the markup language.
 * @copyright Copyright (c) 2022
 */

#include "attribute_types/attribute_base.h"

namespace igm::internal
{

class StringWrapper : public AttributeBase<std::string>
{
public:
    StringWrapper()
        : AttributeBase(AttributeType::kString, std::string())
    { }

    StringWrapper(std::string value)
        : AttributeBase(AttributeType::kString, value)
    { }

    inline operator std::string() { return this->GetValue(); }

    inline std::string ToString() noexcept
    {
        return '"' + this->GetValue() + '"';
    }

private:
    bool LoadValue(std::string value) noexcept;

    bool InitReference(StringWrapper& ref) noexcept;
};

}  // namespace igm::internal

#endif  // IMGUI_MARKUP_SRC_ATTRIBUTE_TYPES_STRING_WRAPPER_H_
