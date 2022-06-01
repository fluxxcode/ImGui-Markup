#include "impch.h"
#include "attribute_types/margin_wrapper.h"

/**
 * @file margin_wrapper.cpp
 * @author FluxxCode (info.fluxxcode@gmail.com)
 * @brief Implementation of margin_wrapper.h
 * @copyright Copyright (c) 2022
 */

#include "attribute_types/vector4_wrapper.h"

namespace igm::internal
{

void MarginWrapper::Init() noexcept
{
    this->InitChildAttribute("top", &this->GetValueReference().top);
    this->InitChildAttribute("right", &this->GetValueReference().right);
    this->InitChildAttribute("bottom", &this->GetValueReference().bottom);
    this->InitChildAttribute("left", &this->GetValueReference().left);
}

bool MarginWrapper::LoadValue(const MarginWrapper& val) noexcept
{
    this->SetValue((bt::Margin)val);
    return true;
}

bool MarginWrapper::LoadValue(const Vector4Wrapper& val) noexcept
{
    this->SetValue(bt::Margin(val.GetValue().x, val.GetValue().y,
        val.GetValue().z, val.GetValue().w));
    return true;
}


bool MarginWrapper::InitReference(MarginWrapper& ref) noexcept
{
    this->IMPL_InitReference((AttributeBase<bt::Margin>*) & ref);
    return true;
}

}  // namespace igm::internal
