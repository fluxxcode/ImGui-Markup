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
    this->AddAttribute("int_value", &this->int_value_);
    this->AddAttribute("float_value", &this->float_value_);
    this->AddAttribute("bool_value", &this->bool_value_);
    this->AddAttribute("string_value", &this->string_value_);
    this->AddAttribute("vec2_value", &this->vec2_value_);
    this->AddAttribute("vec4_value", &this->vec4_value_);
    this->AddAttribute("padding_value", &this->padding_value_);
    this->AddAttribute("margin_value", &this->margin_value_);
    this->AddAttribute("orientation_value", &this->orientation_value_);
}

void Panel::API_Update() noexcept
{
    std::cout << "######" << this->access_id_ << "######" << std::endl;

    std::cout << "INT: " << this->int_value_.ToString() << std::endl;
    std::cout << "FLOAT: " << this->float_value_.ToString() << std::endl;
    std::cout << "BOOL: " << this->bool_value_.ToString() << std::endl;
    std::cout << "STRING: " << this->string_value_.ToString() << std::endl;
    std::cout << "VEC2: " << this->vec2_value_.ToString() << std::endl;
    std::cout << "VEC4: " << this->vec4_value_.ToString() << std::endl;
    std::cout << "PADDING: " << this->padding_value_.ToString() << std::endl;
    std::cout << "MARGIN: " << this->margin_value_.ToString() << std::endl;
    std::cout << "ORIENTATION: " << this->orientation_value_.ToString() << std::endl;

    for (const auto& child : this->child_items_)
        child->API_Update();
}

}  // namespace igm::internal
