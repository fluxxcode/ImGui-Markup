#include "impch.h"
#include "items/other/other_base.h"

/**
 * @file other_base.cpp
 * @author FluxxCode (info.fluxxcode@gmail.com)
 * @brief Implementation of other_base.h
 * @copyright Copyright (c) 2022
 */

namespace igm::internal
{

void OtherBase::API_Update(bt::Vector2 position, bt::Vector2 size) noexcept
{
    this->Update(position, size, false, false);
}

}  // namespace igm::internal
