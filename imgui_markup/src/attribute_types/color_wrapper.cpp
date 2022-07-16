#include "impch.h"
#include "attribute_types/color_wrapper.h"

/**
 * @file color_wrapper.cpp
 * @author FluxxCode (info.fluxxcode@gmail.com)
 * @brief Implementation of color_wrapper.h
 * @copyright Copyright (c) 2022
 */

#include "attribute_types/attribute_types.h"

namespace igm::internal
{

void ColorWrapper::Init() noexcept
{
    this->InitChildAttribute("r", this->ValueReference().r);
    this->InitChildAttribute("g", this->ValueReference().g);
    this->InitChildAttribute("b", this->ValueReference().b);
    this->InitChildAttribute("a", this->ValueReference().a);
}

bool ColorWrapper::LoadValue(const ColorWrapper& val) noexcept
{
    this->SetValue((bt::Color)val);
    return true;
}

bool ColorWrapper::LoadValue(const Vector4Wrapper& val) noexcept
{
    this->SetValue(bt::Color(val.Value().x, val.Value().y,
        val.Value().z, val.Value().w));
    return true;
}

bool ColorWrapper::InitReference(ColorWrapper& ref) noexcept
{
    this->IMPL_InitReference((AttributeBase<bt::Color>*) & ref);
    return true;
}

}  // namespace igm::internal
