#include "impch.h"
#include "items/gui/views/view_base.h"

/**
 * @file views_base.cpp
 * @author FluxxCode (info.fluxxcode@gmail.com)
 * @brief Implementation of view_base.h
 * @copyright Copyright (c) 2022 - 2023
 */

namespace igm::internal
{

ViewBase::ViewBase(ItemType type, std::string id, ItemBase* parent,
                   bool clipping_area)
   : GUIBase(type, ItemCategory::kView, id, parent, clipping_area)
{ }

void ViewBase::GUIUpdate(bt::Vector2 position, bt::Vector2 size) noexcept
{
    this->ViewUpdate(position, size);
}

}  // namespace igm::internal
