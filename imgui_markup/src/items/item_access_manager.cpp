#include "impch.h"
#include "items/item_access_manager.h"

/**
 * @file item_access_manager.cpp
 * @author FluxxCode (info.fluxxcode@gmail.com)
 * @copyright Copyright (c) 2022
 */

namespace igm::internal
{

ItemAccessManager::ItemAccessManager()
{ }

ItemAccessManager::~ItemAccessManager()
{
    this->Clear();
}

}  // namespace igm::internal
