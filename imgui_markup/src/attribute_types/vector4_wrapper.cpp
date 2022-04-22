#include "impch.h"
#include "attribute_types/vector4_wrapper.h"

/**
 * @file vector4_wrapper.cpp
 * @author FluxxCode (info.fluxxcode@gmail.com)
 * @brief Implementation of vector4_wrapper.h
 * @copyright Copyright (c) 2022
 */

namespace igm::internal
{

bool Vector4Wrapper::LoadValue(InternalVector4& value) noexcept
{
    this->SetValue(value);
    return true;
}

bool Vector4Wrapper::InitReference(Vector4Wrapper& ref) noexcept
{
    this->IMPL_InitReference((AttributeBase<InternalVector4>*)&ref);
    return true;
}

}  // namespace igm::internal
