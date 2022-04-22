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

bool Vector2Wrapper::LoadValue(InternalVector2& value) noexcept
{
    this->SetValue(value);
    return true;
}

bool Vector2Wrapper::InitReference(Vector2Wrapper& ref) noexcept
{
    this->IMPL_InitReference((AttributeBase<InternalVector2>*)&ref);
    return true;
}

}  // namespace igm::internal
