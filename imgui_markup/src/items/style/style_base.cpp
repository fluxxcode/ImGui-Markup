#include "impch.h"
#include "items/style/style_base.h"

/**
 * @file style_base.cpp
 * @author FluxxCode (info.fluxxcode@gmail.com)
 * @brief Implementation of style_base.h
 * @copyright Copyright (c) 2022
 */

namespace igm::internal
{

StyleBase::StyleBase(ItemType type, std::string id, ItemBase* parent,
                     ItemType expected_item)
    : ItemBase(type, ItemCategory::kStyle, {UnitType::kGUI, UnitType::kTheme},
                id, parent),
      expected_item_(expected_item)
{ }

bool StyleBase::OnProcessStart(std::string& error_message) noexcept
{
    if (!this->parent_)
    {
        error_message = "Style item can not be placed in the global scope.";
        return false;
    }

    ItemType parent_type = this->parent_->GetType();
    if (parent_type != this->expected_item_ &&
        parent_type != ItemType::kTheme)
    {
        error_message = "Unexpected parent type. Make sure the style item is "
                        "placed in a Theme or in the correct item.";
        return false;
    }

    if (parent_type == this->expected_item_)
        this->parent_->InitStyle(*this);

    return true;
}

} // namespace igm::internal
