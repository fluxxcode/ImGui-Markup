#include "impch.h"
#include "items/attribute_types.h"

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

// IntWrapper
bool IntWrapper::LoadValue(std::string value) noexcept
{
    int temp;
    if (!utils::StringToInt(value, temp))
        return false;

    this->SetValue(temp);
    return true;
}

bool IntWrapper::LoadValue(int value) noexcept
{
    this->SetValue(value);
    return true;
}

bool IntWrapper::LoadValue(float value) noexcept
{
    this->SetValue(value);
    return true;
}

bool IntWrapper::InitReference(IntWrapper& ref) noexcept
{
    this->IMPL_InitReference((AttributeBase<int>*)&ref);
    return true;
}

// FloatWrapper
bool FloatWrapper::LoadValue(std::string value) noexcept
{
    float temp;
    if (!utils::StringToFloat(value, temp))
        return false;

    this->SetValue(temp);
    return true;
}

bool FloatWrapper::LoadValue(float value) noexcept
{
    this->SetValue(value);
    return true;
}

bool FloatWrapper::LoadValue(int value) noexcept
{
    this->SetValue(value);
    return true;
}

bool FloatWrapper::InitReference(FloatWrapper& ref) noexcept
{
    this->IMPL_InitReference((AttributeBase<float>*)&ref);
    return true;
}

// BoolWrapper
bool BoolWrapper::LoadValue(std::string value) noexcept
{
    bool temp;
    if (!utils::StringToBool(value, temp))
        return false;

    this->SetValue(temp);
    return true;
}

bool BoolWrapper::LoadValue(bool value) noexcept
{
    this->SetValue(value);
    return true;
}

bool BoolWrapper::InitReference(BoolWrapper& ref) noexcept
{
    this->IMPL_InitReference((AttributeBase<bool>*)&ref);
    return true;
}

// StringWrapper
bool StringWrapper::LoadValue(std::string value) noexcept
{
    this->SetValue(value);
    return true;
}

bool StringWrapper::InitReference(StringWrapper& ref) noexcept
{
    this->IMPL_InitReference((AttributeBase<std::string>*)&ref);
    return true;
}

// Vector2Wrapper
bool Vector2Wrapper::LoadValue(Vector2 value) noexcept
{
    this->SetValue(InternalVector2(value.x, value.y));
    return true;
}

bool Vector2Wrapper::InitReference(Vector2Wrapper& ref) noexcept
{
    this->IMPL_InitReference((AttributeBase<InternalVector2>*)&ref);
    return true;
}

// Vector4Wrapper
bool Vector4Wrapper::LoadValue(Vector4 value) noexcept
{
    this->SetValue(InternalVector4(value.x, value.y, value.z, value.w));
    return true;
}

bool Vector4Wrapper::InitReference(Vector4Wrapper& ref) noexcept
{
    this->IMPL_InitReference((AttributeBase<InternalVector4>*)&ref);
    return true;
}

}  // namespace igm::internal
