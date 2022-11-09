#include "impch.h"
#include "items/other/container.h"

/**
 * @file container.cpp
 * @author FluxxCode (info.fluxxcode@gmail.com)
 * @brief Implementation of container.h
 * @copyright Copyright (c) 2022
 */

namespace igm::internal
{

Container::Container(std::string id, ItemBase* parent)
    : OtherBase(ItemType::kContainer, id, parent)
{ }

bool Container::OnProcessEnd(std::string& error_message) noexcept
{
    if (this->child_items_.size() != 0)
    {
        error_message = "Item of type Container can not hold any child items.";
        return false;
    }

    return true;
}

}  // namespace igm::internal
