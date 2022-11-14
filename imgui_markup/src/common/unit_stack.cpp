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

UnitBase& UnitStack::CreateEmptyUnit(UnitType type)
{
    return UnitStack::Get().IMPL_CreateEmptyUnit(type);
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

UnitBase* UnitStack::GetUnit(size_t unit, bool* result)
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

UnitBase& UnitStack::IMPL_CreateEmptyUnit(UnitType type)
{
    const size_t unit_id = ++this->unit_count_;

    switch (type)
    {
    case UnitType::kGUI:
        this->unit_stack_.emplace(unit_id, std::make_unique<GUIUnit>(unit_id));
        break;
    default:
        assert("Invalid unit type");
        break;
    }

    UnitBase& unit = *this->unit_stack_.at(unit_id).get();

    return unit;
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

UnitBase* UnitStack::IMPL_GetUnit(size_t unit, bool* result)
{
    if (result)
        *result = false;

    if (this->unit_stack_.find(unit) == this->unit_stack_.end())
    {
        this->last_results_[unit] = Result(ResultType::kInvalidUnitID,
                                           "InvalidUnitID");
        return nullptr;
    }

    if (result)
        *result = true;

    return this->unit_stack_.at(unit).get();
}

ItemAPI* UnitStack::IMPL_GetItemAPI(size_t unit_id, const char* item_id,
                                    bool* result)
{
    UnitBase* unit = this->IMPL_GetUnit(unit_id, result);
    if (!unit)
        return nullptr;

    if (unit->GetItemMapping().find(item_id) == unit->GetItemMapping().end())
    {
        this->last_results_[unit_id] = Result(ResultType::kInvalidItemID,
                                              "InvalidItemID");
        return nullptr;
    }

    if (result)
        *result = true;

    return dynamic_cast<ItemAPI*>(unit->GetItemMapping().at(item_id));
}

}  // namespace igm::internal
