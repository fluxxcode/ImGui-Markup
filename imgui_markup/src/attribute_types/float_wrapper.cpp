#include "impch.h"
#include "attribute_types/float_wrapper.h"

/**
 * @file float_wrapper.cpp
 * @author FluxxCode (info.fluxxcode@gmail.com)
 * @brief Implementation of float_wrapper.h
 * @copyright Copyright (c) 2022
 */

#include "attribute_types/int_wrapper.h"
#include "utility/utility.h"

namespace igm::internal
{

bool FloatWrapper::LoadValue(const FloatWrapper& val) noexcept
{
    this->SetValue((float)val);
    return true;
}

bool FloatWrapper::LoadValue(const IntWrapper& val) noexcept
{
    this->SetValue((float)(int)val);
    return true;
}

bool FloatWrapper::InitReference(FloatWrapper& ref) noexcept
{
    this->IMPL_InitReference((AttributeBase<float>*)&ref);
    return true;
}

}  // namespace igm::internal
