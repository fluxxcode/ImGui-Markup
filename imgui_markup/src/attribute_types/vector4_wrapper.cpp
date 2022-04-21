#include "impch.h"
#include "attribute_types/vector4_wrapper.h"

namespace igm::internal
{

bool Vector4Wrapper::LoadValue(InternalVector4& value) noexcept
{
    this->SetValue(value);
    return true;
}

bool Vector4Wrapper::InitReference(Vector4Wrapper& ref) noexcept
{
    this->IMPL_InitReference((AttributeBase<InternalVector4>*)&ref);
    return true;
}

}  // namespace igm::internal
