#include "impch.h"
#include "items/style/theme.h"

/**
 * @file theme.cpp
 * @author FluxxCode (info.fluxxcode@gmail.com)
 * @brief Implementation of theme.h
 * @copyright Copyright (c) 2022 - 2023
 */

#include "items/style/style_base.h"

namespace igm::internal
{

Theme::Theme(std::string id, ItemBase* parent)
    : ItemBase(ItemType::kTheme, ItemCategory::kOther, id, parent)
{
    this->InitAttribute("name", this->name_);
}

bool Theme::OnProcessEnd(std::string& error_message) noexcept
{
    for (const auto& child : this->child_items_)
    {
        if (child->GetCategory() == ItemCategory::kStyle)
            continue;

        error_message = "Item of type Theme can only hold items of "
                        "category Style";
        return false;
    }

    return true;
}

}  // namespace igm::internal
