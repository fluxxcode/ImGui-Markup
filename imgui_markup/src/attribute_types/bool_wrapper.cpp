#include "impch.h"
#include "attribute_types/bool_wrapper.h"

#include "utility/utility.h"

namespace igm::internal
{

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

}  // namespace igm::internal
