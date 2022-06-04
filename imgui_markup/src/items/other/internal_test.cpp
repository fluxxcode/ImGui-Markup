#include "impch.h"
#include "items/other/internal_test.h"

/**
 * @file internal_test.cpp
 * @author FluxxCode (info.fluxxcode@gmail.com)
 * @brief Implementation of internal_test.h
 * @copyright Copyright (c) 2022
 */

namespace igm::internal
{

InternalTest::InternalTest(std::string id, ItemBase* parent)
    : OtherBase(ItemType::kInternalTest, id, parent)
{
    this->AddAttribute("int_value", &this->int_value_);
    this->AddAttribute("float_value", &this->float_value_);
    this->AddAttribute("bool_value", &this->bool_value_);
    this->AddAttribute("string_value", &this->string_value_);
    this->AddAttribute("vec2_value", &this->vec2_value_);
    this->AddAttribute("vec4_value", &this->vec4_value_);
    this->AddAttribute("padding_value", &this->padding_value_);
    this->AddAttribute("margin_value", &this->margin_value_);
    this->AddAttribute("color_value", &this->color_value_);
    this->AddAttribute("orientation_value", &this->orientation_value_);
}

void InternalTest::Update(bt::Vector2 position, bt::Vector2 size) noexcept
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
    std::cout << "COLOR: " << this->color_value_.ToString() << std::endl;
    std::cout << "ORIENTATION: " << this->orientation_value_.ToString() << std::endl;

    for (const auto& child : this->child_items_)
        child->Update(position, size);
}

}  // namespace igm::internal
