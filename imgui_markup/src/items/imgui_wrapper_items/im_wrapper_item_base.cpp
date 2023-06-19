#include "impch.h"
#include "items/imgui_wrapper_items/im_wrapper_item_base.h"

/**
 * @file im_wrapper_item_base.cpp
 * @author FluxxCode (info.fluxxcode@gmail.com)
 * @brief Implementation of im_wrapper_item_base.h
 * @copyright Copyright (c) 2022 - 2023
 */

namespace igm::internal
{

ImWrapperItemBase::ImWrapperItemBase(ItemType type, std::string id,
                                     ItemBase* parent)
    : ItemBase(type, ItemCategory::kImGuiWrapper, id, parent)
{ }

}  // namespace igm::internal
