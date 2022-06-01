#include "impch.h"
#include "attribute_types/attribute_base.h"

/**
 * @file attribute_base.cpp
 * @author FluxxCode (info.fluxxcode@gmail.com)
 * @brief Implementation of attribute_base.h
 * @copyright Copyright (c) 2022
 */

#include "attribute_types/attribute_types.h"
#include "utility/utility.h"

namespace igm::internal
{

bool AttributeInterface::LoadValue(const AttributeInterface& ref) noexcept
{
    switch (ref.GetType())
    {
    case AttributeType::kInt:
        return this->LoadValue((const IntWrapper&)ref);
    case AttributeType::kFloat:
        return this->LoadValue((const FloatWrapper&)ref);
    case AttributeType::kBool:
        return this->LoadValue((const BoolWrapper&)ref);
    case AttributeType::kString:
        return this->LoadValue((const StringWrapper&)ref);
    case AttributeType::kVector2:
        return this->LoadValue((const Vector2Wrapper&)ref);
    case AttributeType::kVector4:
        return this->LoadValue((const Vector4Wrapper&)ref);
    case AttributeType::kPadding:
        return this->LoadValue((const PaddingWrapper&)ref);
    case AttributeType::kMargin:
        return this->LoadValue((const MarginWrapper&)ref);
    case AttributeType::kColor:
        return this->LoadValue((const ColorWrapper&)ref);
    case AttributeType::kOrientation:
        return this->LoadValue((const OrientationWrapper&)ref);
    default: return false;;
    }

    return false;
}

bool AttributeInterface::InitReference(AttributeInterface& ref) noexcept
{
    switch (ref.GetType())
    {
    case AttributeType::kInt:
        return this->InitReference((IntWrapper&)ref);
    case AttributeType::kFloat:
        return this->InitReference((FloatWrapper&)ref);
    case AttributeType::kBool:
        return this->InitReference((BoolWrapper&)ref);
    case AttributeType::kString:
        return this->InitReference((StringWrapper&)ref);
    case AttributeType::kVector2:
        return this->InitReference((Vector2Wrapper&)ref);
    case AttributeType::kVector4:
        return this->InitReference((Vector4Wrapper&)ref);
    case AttributeType::kPadding:
        return this->InitReference((PaddingWrapper&)ref);
    case AttributeType::kMargin:
        return this->InitReference((MarginWrapper&)ref);
    case AttributeType::kColor:
        return this->InitReference((ColorWrapper&)ref);
    case AttributeType::kOrientation:
        return this->InitReference((OrientationWrapper&)ref);
    default: return false;;
    }

    return false;
}

}  // namespace igm::internal
