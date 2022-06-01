#ifndef IMGUI_MARKUP_SRC_ATTRIBUTE_TYPES_PADDING_WRAPPER_H_
#define IMGUI_MARKUP_SRC_ATTRIBUTE_TYPES_PADDING_WRAPPER_H_

/**
 * @file padding_wrapper.h
 * @author FluxxCode (info.fluxxcode@gmail.com)
 * @brief Contains wrapper above the internal padding.
 *        Used internally by the markup language.
 * @copyright Copyright (c) 2022
 */

#include "attribute_types/internal/padding.h"
#include "attribute_types/attribute_base.h"

#include <string>  // std::string

namespace igm::internal
{

class PaddingWrapper : public AttributeBase<at::Padding>
{
public:
    PaddingWrapper()
        : AttributeBase(AttributeType::kPadding, at::Padding())
    {
        this->Init();
    }

    PaddingWrapper(float top, float right, float bottom, float left)
        : AttributeBase(AttributeType::kPadding,
                        at::Padding((FloatWrapper)top, (FloatWrapper)right,
                                    (FloatWrapper)bottom, (FloatWrapper)left))
    {
        this->Init();
    }

    PaddingWrapper(at::Padding value)
        : AttributeBase(AttributeType::kPadding, value)
    {
        this->Init();
    }

    inline operator at::Padding() const
    {
        return this->GetValue();
    }

    inline std::string GetName() const noexcept { return "Padding"; }

    inline std::string ToString() const noexcept
    {
        at::Padding val = this->GetValue();
        return val.top.ToString() + "," + val.right.ToString() + "," +
               val.bottom.ToString() + "," + val.left.ToString();
    }

private:
    void Init() noexcept;

    bool LoadValue(const PaddingWrapper& val) noexcept;
    bool LoadValue(const Vector4Wrapper& val) noexcept;

    bool InitReference(PaddingWrapper& ref) noexcept;
};

}  // namespace igm::internal

#endif  // IMGUI_MARKUP_SRC_ATTRIBUTE_TYPES_PADDING_WRAPPER_H_
