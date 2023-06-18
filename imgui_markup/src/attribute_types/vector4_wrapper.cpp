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

void Vector4Wrapper::Init() noexcept
{
    this->InitChildAttribute("x", this->ValueReference().x);
    this->InitChildAttribute("y", this->ValueReference().y);
    this->InitChildAttribute("z", this->ValueReference().z);
    this->InitChildAttribute("w", this->ValueReference().w);
}

bool Vector4Wrapper::LoadValue(const Vector4Wrapper& val) noexcept
{
    this->SetValue(val.Value());
    return true;
}

bool Vector4Wrapper::InitReference(Vector4Wrapper& ref) noexcept
{
    this->IMPL_InitReference((AttributeBase<bt::Vector4>*)&ref);
    return true;
}

}  // namespace igm::internal
