#ifndef IMGUI_MARKUP_SRC_ATTRIBUTE_TYPES_DIRECTION_WRAPPER_H_
#define IMGUI_MARKUP_SRC_ATTRIBUTE_TYPES_DIRECTION_WRAPPER_H_

/**
 * @file direction_wrapper.h
 * @author FluxxCode (info.fluxxcode@gmail.com)
 * @brief Contains wrapper above the direction enum
 * @copyright Copyright (c) 2022 - 2023
 */

#include "attribute_types/attribute_base.h"
#include "attribute_types/base_types/direction.h"

#include <string>  // std::string

namespace igm::internal
{

class DirectionWrapper : public AttributeBase<bt::Direction>
{
public:
    DirectionWrapper(bt::Direction value)
        : AttributeBase(AttributeType::kDirection, value)
    { }

    inline void operator = (const DirectionWrapper& val)
    {
        this->SetValue(val);
    }

    operator bt::Direction() const { return this->Value(); }

    inline std::string GetName() const noexcept { return "Direction"; }

    inline std::string ToString() const noexcept
    {
        switch(this->Value())
        {
        case bt::Direction::kLeft: return "Direction::Left";
        case bt::Direction::kRight: return "Direction::Right";
        case bt::Direction::kUp: return "Direction::Up";
        case bt::Direction::kDown: return "Direction::Down";
        default: return "Direction::UNDEFINED";
        }
    }

private:
    bool LoadValue(const DirectionWrapper& val) noexcept;
    bool LoadValue(const StringWrapper& val) noexcept;

    bool InitReference(DirectionWrapper& ref) noexcept;
};

}  // namespace igm::internal

#endif  // IMGUI_MARKUP_SRC_ATTRIBUTE_TYPES_DIRECTION_WRAPPER_H_
