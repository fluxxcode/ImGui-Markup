#include "impch.h"
#include "common/units/theme_unit.h"

/**
 * @file theme_unit.cpp
 * @author FluxxCode (info.fluxxcode@gmail.com)
 * @brief Implementation of theme_unit.h
 * @copyright Copyright (c) 2022
 */

namespace igm::internal
{

ThemeUnit::ThemeUnit(const size_t unit_id)
    : UnitBase(unit_id, UnitType::kTheme)
{ }

std::vector<const char*> ThemeUnit::GetLoadedThemes() const noexcept
{
    std::vector<const char*> ids = std::vector<const char*>();
    for (auto const& [key, val] : this->item_id_mapping_)
    {
        if (val->GetType() == ItemType::kTheme)
            ids.push_back(key.c_str());
    }
    return ids;
}

}  // namespace igm::internal
