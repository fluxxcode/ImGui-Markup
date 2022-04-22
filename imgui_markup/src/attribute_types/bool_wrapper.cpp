#include "impch.h"
#include "attribute_types/bool_wrapper.h"

/**
 * @file bool_wrapper.cpp
 * @author FluxxCode (info.fluxxcode@gmail.com)
 * @brief Implementation of bool_wrapper.h
 * @copyright Copyright (c) 2022
 */

#include "utility/utility.h"

namespace igm::internal
{

bool BoolWrapper::LoadValue(const BoolWrapper& val) noexcept
{
    this->SetValue((bool)val);
    return true;
}

bool BoolWrapper::InitReference(BoolWrapper& ref) noexcept
{
    this->IMPL_InitReference((AttributeBase<bool>*)&ref);
    return true;
}

}  // namespace igm::internal
