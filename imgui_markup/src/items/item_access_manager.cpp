#include "impch.h"
#include "items/item_access_manager.h"

/**
 * @file item_access_manager.cpp
 * @author FluxxCode (info.fluxxcode@gmail.com)
 * @copyright Copyright (c) 2022 - 2023
 */

#include "items/item_base.h"

namespace igm::internal
{

ItemAccessManager::ItemAccessManager()
{ }

ItemAccessManager::~ItemAccessManager()
{
    this->Clear();
}

void ItemAccessManager::TrackItem(ItemBase& item) noexcept
{
    if (this->item_)
        this->Clear();
    item.TrackItemAccessManager(*this);
    this->item_ = &item;
}

void ItemAccessManager::Clear() noexcept
{
    if (this->item_)
        this->item_->LoseItemAccessManager(*this);
    this->item_ = nullptr;
}

}  // namespace igm::internal
