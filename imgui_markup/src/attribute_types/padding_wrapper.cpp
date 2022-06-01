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

void PaddingWrapper::Init() noexcept
{
    this->InitChildAttribute("top",    &this->GetValueReference().top);
    this->InitChildAttribute("right",  &this->GetValueReference().right);
    this->InitChildAttribute("bottom", &this->GetValueReference().bottom);
    this->InitChildAttribute("left",   &this->GetValueReference().left);
}

bool PaddingWrapper::LoadValue(const PaddingWrapper& val) noexcept
{
    this->SetValue((bt::Padding)val);
    return true;
}

bool PaddingWrapper::LoadValue(const Vector4Wrapper& val) noexcept
{
    this->SetValue(bt::Padding(val.GetValue().x, val.GetValue().y,
                               val.GetValue().z, val.GetValue().w));
    return true;
}


bool PaddingWrapper::InitReference(PaddingWrapper& ref) noexcept
{
    this->IMPL_InitReference((AttributeBase<bt::Padding>*)&ref);
    return true;
}

}  // namespace igm::internal
