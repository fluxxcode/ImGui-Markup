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

void ThemeUnit::Update(size_t display_width, size_t display_height) noexcept
{
    for (const auto& child : this->item_tree_)
    {
        child->API_Update(internal::bt::Vector2(0, 0),
                          internal::bt::Vector2(display_width, display_height));
    }
}

}  // namespace igm::internal
