#include "impch.h"
#include "common/units/unit_base.h"

/**
 * @file unit_base.cpp
 * @author FluxxCode (info.fluxxcode@gmail.com)
 * @brief Implementation of unit_base.h
 * @copyright Copyright (c) 2022
 */

namespace igm::internal
{

UnitBase::UnitBase(const size_t unit_id, const UnitType unit_type)
    : unit_id_(unit_id), unit_type_(unit_type)
{ }

void UnitBase::Clear() noexcept
{
    this->item_tree_.clear();
    this->item_id_mapping_.clear();
}

}  // namespace igm::internal
