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

void UnitStack::SetLastResult(size_t unit, Result result)
{
    return UnitStack::Get().IMPL_SetLastResult(unit, result);
}

Result UnitStack::GetLastResult(size_t unit, bool* result)
{
    return UnitStack::Get().IMPL_GetLastResult(unit, result);
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

void UnitStack::IMPL_DeleteUnit(size_t unit, bool* result)
{
    if (result)
        *result = false;

    if (this->unit_stack_.find(unit) == this->unit_stack_.end())
        return;

    if (result)
        *result = true;

    this->unit_stack_.erase(unit);
    this->last_results_.erase(unit);
}

void UnitStack::IMPL_SetLastResult(size_t unit, Result result)
{
    this->last_results_[unit] = result;
}

Result UnitStack::IMPL_GetLastResult(size_t unit, bool* result)
{
    if (result)
        *result = false;

    if (this->last_results_.find(unit) == this->last_results_.end())
        return Result();

    if (result)
        *result = true;

    return this->last_results_.at(unit);
}

}  // namespace igm::internal
