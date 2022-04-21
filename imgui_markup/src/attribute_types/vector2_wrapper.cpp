#include "impch.h"
#include "attribute_types/vector2_wrapper.h"

namespace igm::internal
{

bool Vector2Wrapper::LoadValue(InternalVector2& value) noexcept
{
    this->SetValue(value);
    return true;
}

bool Vector2Wrapper::InitReference(Vector2Wrapper& ref) noexcept
{
    this->IMPL_InitReference((AttributeBase<InternalVector2>*)&ref);
    return true;
}

}  // namespace igm::internal
