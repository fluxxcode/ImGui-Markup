#include "impch.h"
#include "items/item_base.h"

/**
 * @file item_base.cpp
 * @author FluxxCode (info.fluxxcode@gmail.com)
 * @brief Implementation of item_base.h
 * @copyright Copyright (c) 2022
 */

#include "items/item_factory.h"
#include "items/item_access_manager.h"

#include "items/style/style_base.h"

namespace igm::internal
{

ItemBase::ItemBase(ItemType type, ItemCategory category,
                   std::vector<UnitType> unit_types, std::string id,
                   ItemBase* parent)
    : type_(type), category_(category), unit_types_(unit_types), access_id_(id),
      parent_(parent)
{
    const void* address = static_cast<const void*>(this);
    std::stringstream ss;
    ss << address;
    this->unique_id_ = ss.str();
}

ItemBase::~ItemBase()
{
    for (auto item : this->tracked_access_manager_)
        item->Clear();
}

ItemBase* ItemBase::CreateChildItem(std::string type, std::string id) noexcept
{
    this->child_items_.push_back(ItemFactory::CreateItem(type, id, this));

    if (this->child_items_.back() == nullptr)
    {
        this->child_items_.pop_back();
        return nullptr;
    }

    return this->child_items_.back().get();
}

void ItemBase::Update(bt::Vector2 position, bt::Vector2 available_size,
                      bool dynamic_w, bool dynamic_h) noexcept
{
    for (auto const* style : this->style_items_)
    {
        if (style)
            style->PushStyle();
    }

    this->ItemUpdate(position, available_size, dynamic_w, dynamic_h);

    for (auto const* style : this->style_items_)
    {
        if (style)
            style->PopStyle();
    }
}

void ItemBase::InitStyle(StyleBase& style) noexcept
{
    this->style_items_.push_back(&style);
}

void ItemBase::TrackItemAccessManager(ItemAccessManager& access_manager)
    noexcept
{
    this->tracked_access_manager_.push_back(&access_manager);
}

void ItemBase::LoseItemAccessManager(ItemAccessManager& access_manager) noexcept
{
    this->tracked_access_manager_.erase(
        std::remove(this->tracked_access_manager_.begin(),
                    this->tracked_access_manager_.end(),
                    &access_manager),
        this->tracked_access_manager_.end());
}


void ItemBase::API_Update(bt::Vector2 position, bt::Vector2 size) noexcept
{
    this->Update(position, size, false, false);
}

}  // namespace igm::internal

