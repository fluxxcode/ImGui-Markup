#ifndef IMGUI_MARKUP_SRC_ATTRIBUTE_TYPES_ORIENTATION_WRAPPER_H_
#define IMGUI_MARKUP_SRC_ATTRIBUTE_TYPES_ORIENTATION_WRAPPER_H_

/**
 * @file enums.h
 * @author FluxxCode (info.fluxxcode@gmail.com)
 * @brief Contains enum classes used internally by the markup language.
 * @copyright Copyright (c) 2022
 */

#include "attribute_types/attribute_base.h"
#include "attribute_types/base_types/orientation.h"

#include <string>  // std::string

namespace igm::internal
{

class OrientationWrapper : public AttributeBase<bt::Orientation>
{
public:
    OrientationWrapper(bt::Orientation value)
        : AttributeBase(AttributeType::kOrientation, value)
    { }

    operator bt::Orientation() const { return this->GetValue(); }

    inline std::string GetName() const noexcept { return "Orientation"; }

    inline std::string ToString() const noexcept
    {
        switch(this->GetValue())
        {
        case bt::Orientation::kHorizontal: return "Orientation::Horizontal";
        case bt::Orientation::kVertical: return "Orientation::Vertical";
        default: return "Orientation::UNDEFINED";
        }
    }

private:
    bool LoadValue(const OrientationWrapper& val) noexcept;
    bool LoadValue(const StringWrapper& val) noexcept;

    bool InitReference(OrientationWrapper& ref) noexcept;
};

}  // namespace igm::internal

#endif  // IMGUI_MARKUP_SRC_ATTRIBUTE_TYPES_ORIENTATION_WRAPPER_H_
