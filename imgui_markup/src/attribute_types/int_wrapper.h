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

#include <string>  // std::string

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

    inline operator int() const { return this->GetValue(); }

    inline IntWrapper& operator+=(IntWrapper rhs) noexcept
    {
        int& ref = this->GetValueReference();
        ref += rhs.GetValue();
        return *this;
    }

    inline IntWrapper& operator+=(int rhs) noexcept
    {
        int& ref = this->GetValueReference();
        ref += rhs;
        return *this;
    }

    inline IntWrapper& operator-=(IntWrapper rhs) noexcept
    {
        int& ref = this->GetValueReference();
        ref -= rhs.GetValue();
        return *this;
    }

    inline IntWrapper& operator-=(int rhs) noexcept
    {
        int& ref = this->GetValueReference();
        ref -= rhs;
        return *this;
    }

    inline std::string GetName() const noexcept { return "Int"; }

    inline std::string ToString() const noexcept
    {
        return std::to_string(this->GetValue());
    }

private:
    bool LoadValue(const IntWrapper& val) noexcept;
    bool LoadValue(const FloatWrapper& val) noexcept;

    bool InitReference(IntWrapper& ref) noexcept;
};

}  // namespace igm::internal

#endif  // IMGUI_MARKUP_SRC_ATTRIBUTE_TYPES_INT_WRAPPER_H_
