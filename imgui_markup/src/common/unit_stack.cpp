#include "impch.h"
#include "common/unit_stack.h"

/**
 * @file unit_stack.cpp
 * @author FluxxCode (info.fluxxcode@gmail.com)
 * @brief Implementation of unit_stack.h
 * @copyright Copyright (c) 2022
 */

namespace igm::internal
{

Unit& UnitStack::CreateEmptyUnit()
{
    return UnitStack::Get().IMPL_CreateEmptyUnit();
}

void UnitStack::DeleteUnit(size_t unit, bool* result)
{
    return UnitStack::Get().IMPL_DeleteUnit(unit, result);
}

void UnitStack::SetLastResult(Result result)
{
    return UnitStack::Get().IMPL_SetLastResult(result);
}

Result UnitStack::GetLastResult()
{
    return UnitStack::Get().IMPL_GetLastResult();
}

Unit* UnitStack::GetUnit(size_t unit, bool* result)
{
    return UnitStack::Get().IMPL_GetUnit(unit, result);
}

ItemAPI* UnitStack::GetItemAPI(size_t unit, const char* item_id, bool* result)
{
    return UnitStack::Get().IMPL_GetItemAPI(unit, item_id, result);
}

UnitStack& UnitStack::Get()
{
    static UnitStack instance;
    return instance;
}

Unit& UnitStack::IMPL_CreateEmptyUnit()
{
    const size_t unit_id = ++this->unit_count_;

    this->unit_stack_.emplace(unit_id, std::make_unique<Unit>(unit_id));
    Unit& unit = *this->unit_stack_.at(unit_id).get();

    return unit;
}

void UnitStack::IMPL_DeleteUnit(size_t unit, bool* result)
{
    if (this->unit_stack_.find(unit) == this->unit_stack_.end())
        return;

    Success(result);

    this->unit_stack_.erase(unit);
}

void UnitStack::IMPL_SetLastResult(Result result)
{
    this->last_result_ = result;
}

Result UnitStack::IMPL_GetLastResult()
{
    return this->last_result_;
}

Unit* UnitStack::IMPL_GetUnit(size_t unit, bool* result)
{

    if (this->unit_stack_.find(unit) == this->unit_stack_.end())
    {
        Error(igm::ResultType::kInvalidUnitID, result);
        return nullptr;
    }

    Success(result);

    return this->unit_stack_.at(unit).get();
}

ItemAPI* UnitStack::IMPL_GetItemAPI(size_t unit_id, const char* item_id,
                                    bool* result)
{
    Unit* unit = this->IMPL_GetUnit(unit_id, result);
    if (!unit)
        return nullptr;

    if (unit->GetItemMapping().find(item_id) == unit->GetItemMapping().end())
    {
        Error(igm::ResultType::kInvalidItemID, result);
        return nullptr;
    }

    Success(result);

    return dynamic_cast<ItemAPI*>(unit->GetItemMapping().at(item_id));
}

}  // namespace igm::internal
