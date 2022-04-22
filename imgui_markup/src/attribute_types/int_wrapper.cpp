#include "impch.h"
#include "attribute_types/int_wrapper.h"

/**
 * @file int_wrapper.cpp
 * @author FluxxCode (info.fluxxcode@gmail.com)
 * @brief Implementation of int_wrapper.h
 * @copyright Copyright (c) 2022
 */

#include "utility/utility.h"

namespace igm::internal
{

bool IntWrapper::LoadValue(std::string value) noexcept
{
    int temp;
    if (!utils::StringToInt(value, temp))
        return false;

    this->SetValue(temp);
    return true;
}

bool IntWrapper::LoadValue(int value) noexcept
{
    this->SetValue(value);
    return true;
}

bool IntWrapper::LoadValue(float value) noexcept
{
    this->SetValue(value);
    return true;
}

bool IntWrapper::InitReference(IntWrapper& ref) noexcept
{
    this->IMPL_InitReference((AttributeBase<int>*)&ref);
    return true;
}

}  // namespace igm::internal
