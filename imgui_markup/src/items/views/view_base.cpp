#include "impch.h"
#include "items/views/view_base.h"

/**
 * @file views_base.cpp
 * @author FluxxCode (info.fluxxcode@gmail.com)
 * @brief Implementation of view_base.h
 * @copyright Copyright (c) 2022
 */

namespace igm::internal
{

void ViewBase::API_Update(bt::Vector2 position, bt::Vector2 size) noexcept
{
    this->Update(position, size);
}

}  // namespace igm::internal
