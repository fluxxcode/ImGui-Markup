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
        case AttributeType::kFloat: return "Int";
        case AttributeType::kBool: return "Int";
        case AttributeType::kString: return "Int";
        case AttributeType::kVector2: return "Int";
        case AttributeType::kVector4: return "Int";
        default: return "UNKNOWN";
    }
}

// IntWrapper
bool IntWrapper::LoadValue(const char* value) noexcept
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

bool IntWrapper::InitReference(IntWrapper& ref) noexcept
{
    this->IMPL_InitReference((AttributeBase<int>*)&ref);
    return true;
}

// FloatWrapper
bool FloatWrapper::LoadValue(const char* value) noexcept
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

bool FloatWrapper::InitReference(FloatWrapper& ref) noexcept
{
    this->IMPL_InitReference((AttributeBase<float>*)&ref);
    return true;
}

// BoolWrapper
bool BoolWrapper::LoadValue(const char* value) noexcept
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
bool StringWrapper::LoadValue(const char* value) noexcept
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
    this->SetValue(value);
    return true;
}

// Vector4Wrapper
bool Vector4Wrapper::LoadValue(Vector4 value) noexcept
{
    this->SetValue(value);
    return true;
}

}  // namespace igm::internal
