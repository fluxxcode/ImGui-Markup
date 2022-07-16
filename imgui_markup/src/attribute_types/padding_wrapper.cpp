#include "impch.h"
#include "attribute_types/padding_wrapper.h"

/**
 * @file padding_wrapper.cpp
 * @author FluxxCode (info.fluxxcode@gmail.com)
 * @brief Implementation of padding_wrapper.h
 * @copyright Copyright (c) 2022
 */

#include "attribute_types/attribute_types.h"

namespace igm::internal
{

void PaddingWrapper::Init() noexcept
{
    this->InitChildAttribute("top",    this->ValueReference().top);
    this->InitChildAttribute("right",  this->ValueReference().right);
    this->InitChildAttribute("bottom", this->ValueReference().bottom);
    this->InitChildAttribute("left",   this->ValueReference().left);
}

bool PaddingWrapper::LoadValue(const PaddingWrapper& val) noexcept
{
    this->SetValue((bt::Padding)val);
    return true;
}

bool PaddingWrapper::LoadValue(const Vector4Wrapper& val) noexcept
{
    this->SetValue(bt::Padding(val.Value().x, val.Value().y,
                               val.Value().z, val.Value().w));
    return true;
}

bool PaddingWrapper::LoadValue(const FloatWrapper& val) noexcept
{
    const float value = val.Value();
    this->SetValue(bt::Padding(value, value, value, value));
    return true;
}

bool PaddingWrapper::LoadValue(const IntWrapper& val) noexcept
{
    const int value = val.Value();
    this->SetValue(bt::Padding(value, value, value, value));
    return true;
}

bool PaddingWrapper::InitReference(PaddingWrapper& ref) noexcept
{
    this->IMPL_InitReference((AttributeBase<bt::Padding>*)&ref);
    return true;
}

}  // namespace igm::internal
