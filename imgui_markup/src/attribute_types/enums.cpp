#include "impch.h"
#include "attribute_types/enums.h"

/**
 * @file enums.cpp
 * @author FluxxCode (info.fluxxcode@gmail.com)
 * @brief Implementation of enums.h
 * @copyright Copyright (c) 2022
 */

#include "attribute_types/string_wrapper.h"

namespace igm::internal
{

bool OrientationWrapper::LoadValue(const StringWrapper& val) noexcept
{
    if (val.ToString() == "Horizontal")
        this->SetValue(Orientation::kHorizontal);
    else if (val.ToString() == "Vertical")
        this->SetValue(Orientation::kVertical);
    else
        return false;

    return true;
}

bool OrientationWrapper::InitReference(OrientationWrapper& ref) noexcept
{
    this->IMPL_InitReference((AttributeBase<Orientation>*)&ref);
    return true;
}

}  // namespace igm::internal
