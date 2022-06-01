#ifndef IMGUI_MARKUP_SRC_ATTRIBUTE_TYPES_VECTOR2_WRAPPER_H_
#define IMGUI_MARKUP_SRC_ATTRIBUTE_TYPES_VECTOR2_WRAPPER_H_

/**
 * @file vector2_wrapper.h
 * @author FluxxCode (info.fluxxcode@gmail.com)
 * @brief Contains wrapper above the internal vector2.
 *        Used internally by the markup language.
 * @copyright Copyright (c) 2022
 */

#include "attribute_types/base_types/vector2.h"
#include "attribute_types/attribute_base.h"

#include <string>  // std::string

namespace igm::internal
{

class Vector2Wrapper : public AttributeBase<bt::Vector2>
{
public:
    Vector2Wrapper()
        : AttributeBase(AttributeType::kVector2, bt::Vector2())
    {
        this->Init();
    }

    Vector2Wrapper(float x, float y)
        : AttributeBase(AttributeType::kVector2,
                        bt::Vector2((FloatWrapper)x, (FloatWrapper)y))
    {
        this->Init();
    }

    Vector2Wrapper(bt::Vector2 value)
        : AttributeBase(AttributeType::kVector2, value)
    {
        this->Init();
    }

    inline operator bt::Vector2() const
    {
        return this->GetValue();
    }

    inline std::string GetName() const noexcept { return "Vector2"; }

    inline std::string ToString() const noexcept
    {
        bt::Vector2 val = this->GetValue();
        return val.x.ToString() + "," + val.y.ToString();
    }

private:
    void Init() noexcept;

    bool LoadValue(const Vector2Wrapper& val) noexcept;

    bool InitReference(Vector2Wrapper& ref) noexcept;
};

}  // namespace igm::internal

#endif  // IMGUI_MARUP_SRC_ATTRIBUTE_TYPES_VECTOR2_WRAPPER_H_
