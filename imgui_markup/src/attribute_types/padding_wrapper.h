#ifndef IMGUI_MARKUP_SRC_ATTRIBUTE_TYPES_PADDING_WRAPPER_H_
#define IMGUI_MARKUP_SRC_ATTRIBUTE_TYPES_PADDING_WRAPPER_H_

/**
 * @file padding_wrapper.h
 * @author FluxxCode (info.fluxxcode@gmail.com)
 * @brief Contains wrapper above the internal padding.
 *        Used internally by the markup language.
 * @copyright Copyright (c) 2022 - 2023
 */

#include "attribute_types/base_types/padding.h"
#include "attribute_types/attribute_base.h"

#include <string>  // std::string

namespace igm::internal
{

class PaddingWrapper : public AttributeBase<bt::Padding>
{
public:
    PaddingWrapper()
        : AttributeBase(AttributeType::kPadding, bt::Padding())
    {
        this->Init();
    }

    PaddingWrapper(float top, float right, float bottom, float left)
        : AttributeBase(AttributeType::kPadding,
                        bt::Padding((FloatWrapper)top, (FloatWrapper)right,
                                    (FloatWrapper)bottom, (FloatWrapper)left))
    {
        this->Init();
    }

    PaddingWrapper(bt::Padding value)
        : AttributeBase(AttributeType::kPadding, value)
    {
        this->Init();
    }

    inline void operator = (const PaddingWrapper& val)
    {
        this->SetValue(val);
    }

    inline operator bt::Padding() const
    {
        return this->Value();
    }

    inline std::string GetName() const noexcept { return "Padding"; }

    inline std::string ToString() const noexcept
    {
        bt::Padding val = this->Value();
        return val.top.ToString() + "," + val.right.ToString() + "," +
               val.bottom.ToString() + "," + val.left.ToString();
    }

private:
    void Init() noexcept;

    bool LoadValue(const PaddingWrapper& val) noexcept;
    bool LoadValue(const Vector4Wrapper& val) noexcept;
    bool LoadValue(const FloatWrapper& val) noexcept;
    bool LoadValue(const IntWrapper& val) noexcept;

    bool InitReference(PaddingWrapper& ref) noexcept;
};

}  // namespace igm::internal

#endif  // IMGUI_MARKUP_SRC_ATTRIBUTE_TYPES_PADDING_WRAPPER_H_
