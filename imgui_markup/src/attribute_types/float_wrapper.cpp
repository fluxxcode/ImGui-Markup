#include "impch.h"
#include "attribute_types/float_wrapper.h"

#include "utility/utility.h"

namespace igm::internal
{

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

}  // namespace igm::internal
