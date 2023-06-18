#include "impch.h"
#include "attribute_types/int_wrapper.h"

/**
 * @file int_wrapper.cpp
 * @author FluxxCode (info.fluxxcode@gmail.com)
 * @brief Implementation of int_wrapper.h
 * @copyright Copyright (c) 2022 - 2023
 */
#include "attribute_types/float_wrapper.h"
#include "utility/utility.h"

namespace igm::internal
{

bool IntWrapper::LoadValue(const IntWrapper& val) noexcept
{
    this->SetValue((int)val);
    return true;
}

bool IntWrapper::LoadValue(const FloatWrapper& val) noexcept
{
    this->SetValue((int)(float)val);
    return true;
}

bool IntWrapper::InitReference(IntWrapper& ref) noexcept
{
    this->IMPL_InitReference((AttributeBase<int>*)&ref);
    return true;
}

}  // namespace igm::internal
