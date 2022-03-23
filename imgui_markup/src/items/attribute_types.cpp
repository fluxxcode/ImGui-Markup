#include "impch.h"
#include "items/attribute_types.h"

#include "utility/utility.h"

namespace igm::internal
{

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

bool StringWrapper::LoadValue(const char* value) noexcept
{
    this->SetValue(value);
    return true;
}

}  // namespace igm::internal
