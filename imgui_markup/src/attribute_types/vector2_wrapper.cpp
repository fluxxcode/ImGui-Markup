#include "impch.h"
#include "attribute_types/vector2_wrapper.h"

/**
 * @file vector2_wrapper.cpp
 * @author FluxxCode (info.fluxxcode@gmail.com)
 * @brief Implementation of vector2_wrapper.h
 * @copyright Copyright (c) 2022
 */

namespace igm::internal
{

void Vector2Wrapper::Init() noexcept
{
    this->InitChildAttribute("x", &this->GetValueReference().x);
    this->InitChildAttribute("y", &this->GetValueReference().y);
}

bool Vector2Wrapper::LoadValue(const Vector2Wrapper& val) noexcept
{
    this->SetValue((at::Vector2)val);
    return true;
}

bool Vector2Wrapper::InitReference(Vector2Wrapper& ref) noexcept
{
    this->IMPL_InitReference((AttributeBase<at::Vector2>*)&ref);
    return true;
}

}  // namespace igm::internal
