#ifndef IMGUI_MARKUP_SRC_ATTRIBUTE_TYPES_COLOR_WRAPPER_H_
#define IMGUI_MARKUP_SRC_ATTRIBUTE_TYPES_COLOR_WRAPPER_H_

/**
 * @file color_wrapper.h
 * @author FluxxCode (info.fluxxcode@gmail.com)
 * @brief Contains wrapper above the internal color.
 *        Used internally by the markup language.
 * @copyright Copyright (c) 2022
 */

#include "attribute_types/base_types/color.h"
#include "attribute_types/attribute_base.h"

#include <string>  // std::string

namespace igm::internal
{

class ColorWrapper : public AttributeBase<bt::Color>
{
public:
    ColorWrapper()
        : AttributeBase(AttributeType::kColor, bt::Color())
    {
        this->Init();
    }

    ColorWrapper(float r, float g, float b, float a)
        : AttributeBase(AttributeType::kColor,
            bt::Color((FloatWrapper)r, (FloatWrapper)g,
                      (FloatWrapper)b, (FloatWrapper)a))
    {
        this->Init();
    }

    ColorWrapper(bt::Color value)
        : AttributeBase(AttributeType::kColor, value)
    {
        this->Init();
    }

    inline operator bt::Color() const
    {
        return this->Value();
    }

    inline std::string GetName() const noexcept { return "Color"; }

    inline std::string ToString() const noexcept
    {
        bt::Color val = this->Value();
        return val.r.ToString() + "," + val.g.ToString() + "," +
               val.b.ToString() + "," + val.a.ToString();
    }

private:
    void Init() noexcept;

    bool LoadValue(const ColorWrapper& val) noexcept;
    bool LoadValue(const Vector4Wrapper& val) noexcept;

    bool InitReference(ColorWrapper& ref) noexcept;
};

}  // namespace igm::internal

#endif  // IMGUI_MARKUP_SRC_ATTRIBUTE_TYPES_COLOR_WRAPPER_H_
