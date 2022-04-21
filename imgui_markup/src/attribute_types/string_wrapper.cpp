#include "impch.h"
#include "attribute_types/string_wrapper.h"

namespace igm::internal
{

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

}  // namespace igm::internal
