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
    this->InitChildAttribute("x", &this->GetValueReference().x);
    this->InitChildAttribute("y", &this->GetValueReference().y);
    this->InitChildAttribute("z", &this->GetValueReference().z);
    this->InitChildAttribute("w", &this->GetValueReference().w);
}

bool Vector4Wrapper::LoadValue(const Vector4Wrapper& val) noexcept
{
    this->SetValue(val.GetValue());
    return true;
}

bool Vector4Wrapper::InitReference(Vector4Wrapper& ref) noexcept
{
    this->IMPL_InitReference((AttributeBase<bt::Vector4>*)&ref);
    return true;
}

}  // namespace igm::internal
