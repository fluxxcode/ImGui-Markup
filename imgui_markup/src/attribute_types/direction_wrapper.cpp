#include "impch.h"
#include "attribute_types/direction_wrapper.h"

/**
 * @file direction_wrapper.cpp
 * @author FluxxCode (info.fluxxcode@gmail.com)
 * @brief Implementation of direction_wrapper.h
 * @copyright Copyright (c) 2022 - 2023
 */

#include "attribute_types/string_wrapper.h"

namespace igm::internal
{

bool DirectionWrapper::LoadValue(const DirectionWrapper& val) noexcept
{
    this->SetValue(val.Value());
    return true;
}

bool DirectionWrapper::LoadValue(const StringWrapper& val) noexcept
{
    if (val.ToString() == "Left")
        this->SetValue(bt::Direction::kLeft);
    else if (val.ToString() == "Right")
        this->SetValue(bt::Direction::kRight);
    else if (val.ToString() == "Up")
        this->SetValue(bt::Direction::kUp);
    else if (val.ToString() == "Down")
        this->SetValue(bt::Direction::kDown);
    else
        return false;

    return true;
}

bool DirectionWrapper::InitReference(DirectionWrapper& ref) noexcept
{
    this->IMPL_InitReference((AttributeBase<bt::Direction>*)&ref);
    return true;
}

}  // namespace igm::internal
