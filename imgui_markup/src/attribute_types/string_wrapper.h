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

#include <string>  // std::string

namespace igm::internal
{

class StringWrapper : public AttributeBase<std::string>
{
public:
    StringWrapper()
        : AttributeBase(AttributeType::kString, std::string())
    { }

    explicit StringWrapper(const char* value)
        : AttributeBase(AttributeType::kString, value)
    { }

    explicit StringWrapper(std::string value)
        : AttributeBase(AttributeType::kString, value)
    { }

    inline operator std::string() const { return this->GetValue(); }

    inline std::string GetString() { return this->GetValueReference(); }

    inline std::string GetName() const noexcept { return "String"; }

    inline std::string ToString() const noexcept
    {
        return this->GetValue();
    }

private:
    bool LoadValue(const StringWrapper& val) noexcept;

    bool InitReference(StringWrapper& ref) noexcept;
};

}  // namespace igm::internal

#endif  // IMGUI_MARKUP_SRC_ATTRIBUTE_TYPES_STRING_WRAPPER_H_
