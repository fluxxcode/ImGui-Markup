#ifndef IMGUI_MARKUP_SRC_ATTRIBUTE_TYPES_MARGIN_WRAPPER_H_
#define IMGUI_MARKUP_SRC_ATTRIBUTE_TYPES_MARGIN_WRAPPER_H_

/**
 * @file margin_wrapper.h
 * @author FluxxCode (info.fluxxcode@gmail.com)
 * @brief Contains wrapper above the internal margin.
 *        Used internally by the markup language.
 * @copyright Copyright (c) 2022
 */

#include "attribute_types/base_types/margin.h"
#include "attribute_types/attribute_base.h"

#include <string>  // std::string

namespace igm::internal
{

class MarginWrapper : public AttributeBase<bt::Margin>
{
public:
    MarginWrapper()
        : AttributeBase(AttributeType::kMargin, bt::Margin())
    {
        this->Init();
    }

    MarginWrapper(float top, float right, float bottom, float left)
        : AttributeBase(AttributeType::kMargin,
            bt::Margin((FloatWrapper)top, (FloatWrapper)right,
                (FloatWrapper)bottom, (FloatWrapper)left))
    {
        this->Init();
    }

    MarginWrapper(bt::Margin value)
        : AttributeBase(AttributeType::kMargin, value)
    {
        this->Init();
    }

    inline operator bt::Margin() const
    {
        return this->Value();
    }

    inline std::string GetName() const noexcept { return "Margin"; }

    inline std::string ToString() const noexcept
    {
        bt::Margin val = this->Value();
        return val.top.ToString() + "," + val.right.ToString() + "," +
            val.bottom.ToString() + "," + val.left.ToString();
    }

private:
    void Init() noexcept;

    bool LoadValue(const MarginWrapper& val) noexcept;
    bool LoadValue(const Vector4Wrapper& val) noexcept;
    bool LoadValue(const FloatWrapper& val) noexcept;
    bool LoadValue(const IntWrapper& val) noexcept;

    bool InitReference(MarginWrapper& ref) noexcept;
};

}  // namespace igm::internal

#endif  // IMGUI_MARKUP_SRC_ATTRIBUTE_TYPES_MARGIN_WRAPPER_H_
