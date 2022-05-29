#ifndef IMGUI_MARKUP_SRC_ATTRIBUTE_TYPES_ENUMS_H_
#define IMGUI_MARKUP_SRC_ATTRIBUTE_TYPES_ENUMS_H_

/**
 * @file enums.h
 * @author FluxxCode (info.fluxxcode@gmail.com)
 * @brief Contains enum classes used internally by the markup language.
 * @copyright Copyright (c) 2022
 */

#include "attribute_types/attribute_base.h"

namespace igm::internal
{

enum class Orientation : unsigned char
{
    kHorizontal,
    kVertical
};

class OrientationWrapper : public AttributeBase<Orientation>
{
public:
    explicit OrientationWrapper(Orientation value)
        : AttributeBase(AttributeType::kOrientation, value)
    { }

    operator Orientation() const { return this->GetValue(); }

    inline std::string GetName() const noexcept { return "TestEnum"; }

    inline std::string ToString() const noexcept
    {
        switch(this->GetValue())
        {
        case Orientation::kHorizontal: return "Orientation::Horizontal";
        case Orientation::kVertical: return "Orientation::Vertical";
        default: return "Orientation::UNDEFINED";
        }
    }

private:
    bool LoadValue(const OrientationWrapper& val) noexcept;
    bool LoadValue(const StringWrapper& val) noexcept;

    bool InitReference(OrientationWrapper& ref) noexcept;
};

}  // namespace igm::internal

#endif  // IMGUI_MARKUP_SRC_ATTRIBUTE_TYPES_ENUMS_H_
