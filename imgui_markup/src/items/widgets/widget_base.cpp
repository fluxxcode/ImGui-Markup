#include "impch.h"
#include "items/widgets/widget_base.h"

/**
 * @file widget_base.cpp
 * @author FluxxCode (info.fluxxcode@gmail.com)
 * @brief Implementation of widget_base.h
 * @copyright Copyright (c) 2022
 */

namespace igm::internal
{

void WidgetBase::API_Update(bt::Vector2 position, bt::Vector2 size) noexcept
{
    this->Update(position, size);
}

}  // namespace igm::internal
