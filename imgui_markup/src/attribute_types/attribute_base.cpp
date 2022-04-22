#include "impch.h"
#include "attribute_types/attribute_base.h"

/**
 * @file attribute_base.cpp
 * @author FluxxCode (info.fluxxcode@gmail.com)
 * @brief Implementation of attribute_base.h
 * @copyright Copyright (c) 2022
 */

#include "attribute_types/bool_wrapper.h"
#include "attribute_types/float_wrapper.h"
#include "attribute_types/int_wrapper.h"
#include "attribute_types/string_wrapper.h"
#include "attribute_types/vector2_wrapper.h"
#include "attribute_types/vector4_wrapper.h"
#include "utility/utility.h"

namespace igm::internal
{

std::string AttributeTypeToString(AttributeType type)
{
    switch (type)
    {
    case AttributeType::kInt: return "Int";
    case AttributeType::kFloat: return "Float";
    case AttributeType::kBool: return "Bool";
    case AttributeType::kString: return "String";
    case AttributeType::kVector2: return "Vector2";
    case AttributeType::kVector4: return "Vector4";
    default: return "UNKNOWN";
    }
}

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
    default: return false;;
    }

    return false;
}

}  // namespace igm::internal
