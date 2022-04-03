#include "impch.h"
#include "common/unit_stack.h"

namespace igm::internal
{

Unit& UnitStack::CreateEmptyUnit()
{
    return UnitStack::Get().IMPL_CreateEmptyUnit();
}

UnitStack& UnitStack::Get()
{
    static UnitStack instance;
    return instance;
}

Unit& UnitStack::IMPL_CreateEmptyUnit()
{
    const size_t unit_id = ++this->unit_count_;

    this->unit_stack_.emplace(unit_id, Unit(unit_id));

    return this->unit_stack_.at(unit_id);
}

}  // namespace igm::internal
