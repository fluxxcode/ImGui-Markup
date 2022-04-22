#include "impch.h"
#include "items/widgets/panel.h"

/**
 * @file panel.cpp
 * @author FluxxCode (info.fluxxcode@gmail.com)
 * @brief Implementation of panel.h
 * @copyright Copyright (c) 2022
 */

namespace igm::internal
{

Panel::Panel(std::string id, ItemBase* parent)
        : WidgetBase(ItemType::kPanel, id, parent)
{
    this->AddAttribute("value_int", &this->value_int_);
    this->AddAttribute("value_float", &this->value_float_);
    this->AddAttribute("value_bool", &this->value_bool_);
    this->AddAttribute("value_string", &this->value_string_);
    this->AddAttribute("value_vec2", &this->value_vec2_);
    this->AddAttribute("value_vec4", &this->value_vec4_);
}

void Panel::API_Update() noexcept
{
    // TODO: Implementation

    std::cout << this->access_id_ << ": Updating panel" << std::endl;

    for (const auto& [key, value] : this->attributes_)
        std::cout << key << ": " << value->ToString() << std::endl;

    for (const auto& child : this->child_items_)
        child->Update();
}

}  // namespace igm::internal
