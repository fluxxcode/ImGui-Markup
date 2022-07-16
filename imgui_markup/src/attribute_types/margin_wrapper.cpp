#include "impch.h"
#include "attribute_types/margin_wrapper.h"

/**
 * @file margin_wrapper.cpp
 * @author FluxxCode (info.fluxxcode@gmail.com)
 * @brief Implementation of margin_wrapper.h
 * @copyright Copyright (c) 2022
 */

#include "attribute_types/attribute_types.h"

namespace igm::internal
{

void MarginWrapper::Init() noexcept
{
    this->InitChildAttribute("top",    this->ValueReference().top);
    this->InitChildAttribute("right",  this->ValueReference().right);
    this->InitChildAttribute("bottom", this->ValueReference().bottom);
    this->InitChildAttribute("left",   this->ValueReference().left);
}

bool MarginWrapper::LoadValue(const MarginWrapper& val) noexcept
{
    this->SetValue((bt::Margin)val);
    return true;
}

bool MarginWrapper::LoadValue(const Vector4Wrapper& val) noexcept
{
    this->SetValue(bt::Margin(val.Value().x, val.Value().y,
        val.Value().z, val.Value().w));
    return true;
}

bool MarginWrapper::LoadValue(const FloatWrapper& val) noexcept
{
    const float value = val.Value();
    this->SetValue(bt::Margin(value, value, value, value));
    return true;
}

bool MarginWrapper::LoadValue(const IntWrapper& val) noexcept
{
    const int value = val.Value();
    this->SetValue(bt::Margin(value, value, value, value));
    return true;
}


bool MarginWrapper::InitReference(MarginWrapper& ref) noexcept
{
    this->IMPL_InitReference((AttributeBase<bt::Margin>*) & ref);
    return true;
}

}  // namespace igm::internal
