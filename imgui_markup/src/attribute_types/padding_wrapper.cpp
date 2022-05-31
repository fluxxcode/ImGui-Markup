#include "impch.h"
#include "attribute_types/padding_wrapper.h"

/**
 * @file padding_wrapper.cpp
 * @author FluxxCode (info.fluxxcode@gmail.com)
 * @brief Implementation of padding_wrapper.h
 * @copyright Copyright (c) 2022
 */

#include "attribute_types/vector4_wrapper.h"

namespace igm::internal
{

bool PaddingWrapper::LoadValue(const PaddingWrapper& val) noexcept
{
    this->SetValue((at::Padding)val);
    return true;
}

bool PaddingWrapper::LoadValue(const Vector4Wrapper& val) noexcept
{
    this->SetValue(at::Padding(val.GetValue().x, val.GetValue().y,
                               val.GetValue().z, val.GetValue().w));
    return true;
}


bool PaddingWrapper::InitReference(PaddingWrapper& ref) noexcept
{
    this->IMPL_InitReference((AttributeBase<at::Padding>*)&ref);
    return true;
}

}  // namespace igm::internal
