#include "impch.h"
#include "attribute_types/string_wrapper.h"

/**
 * @file string_wrapper.cpp
 * @author FluxxCode (info.fluxxcode@gmail.com)
 * @brief Implementation of string_wrapper.h
 * @copyright Copyright (c) 2022
 */

namespace igm::internal
{

bool StringWrapper::LoadValue(std::string value) noexcept
{
    this->SetValue(value);
    return true;
}

bool StringWrapper::InitReference(StringWrapper& ref) noexcept
{
    this->IMPL_InitReference((AttributeBase<std::string>*)&ref);
    return true;
}

}  // namespace igm::internal
