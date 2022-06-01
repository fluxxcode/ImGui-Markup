#include "impch.h"
#include "parser/interpreter.h"

/**
 * @file interpreter.cpp
 * @author FluxxCode (info.fluxxcode@gmail.com)
 * @brief Implementation of interpreter.h
 * @copyright Copyright (c) 2022
 */

#include "items/item_factory.h"
#include "utility/utility.h"
#include "attribute_types/vector2_wrapper.h"
#include "attribute_types/vector4_wrapper.h"

namespace igm::internal
{

Interpreter::Interpreter(Unit& unit)
    : unit_(unit)
{ }

void Interpreter::Reset() noexcept
{
    this->unit_.item_tree.clear();
    this->unit_.item_ids.clear();
    this->item_stack_.clear();
}

void Interpreter::CreateItem(const Lexer::Token& type, const Lexer::Token& id)
{
    if (id.value.find('.') != std::string::npos)
        throw InvalidCharacterInID(id, '.');

    ItemBase* new_item = nullptr;

    if (this->item_stack_.empty())
    {
        // Item stack is empty; create item within the root of the
        // unit's item tree
        this->unit_.item_tree.push_back(
            ItemFactory::CreateItem(type.value, id.value, nullptr));

        new_item = this->unit_.item_tree.back().get();
    }
    else
    {
        // Create the item within the item that is currently on top
        // of the item stack.
        new_item = this->item_stack_.back()->CreateChildItem(
            type.value, id.value);
    }

    if (new_item == nullptr)
        throw UndefinedItemType(type);

    this->item_stack_.push_back(new_item);

    if (id.value.empty())
        return;

    std::string full_id = this->GetCurrentID();

    // Make sure that there is no other item with the same ID
    if (this->unit_.item_ids.find(full_id) != this->unit_.item_ids.end())
        throw IDIsAlreadyDefined(id);

    this->unit_.item_ids[full_id] = new_item;
}

void Interpreter::PopItem(const Lexer::Token& token)
{
    if (this->item_stack_.empty())
        throw ExpectedItemDeclaration(token);

    this->item_stack_.pop_back();
}

void Interpreter::ProcessAssignAttributeNode(
    Interpreter::AttributeAssignNode node)
{
    AttributeInterface* attribute =
        this->GetAttributeFromCurrentItem(node.name);

    this->AssignAttribute(*attribute, node.value);
}

void Interpreter::ProcessAttributeCreateNode(
    Interpreter::AttributeCreateNode node)
{
    if (this->item_stack_.empty())
        throw CreateAttributeInGlobalScope(node.name);

    ItemBase* item = this->item_stack_.back();

    const std::string& type = node.type.value;
    const std::string& name = node.name.value;

    bool is_valid_name = false;
    if (type == "int")
        is_valid_name = item->CreateAttribute<IntWrapper>(name);
    else if (type == "float")
        is_valid_name = item->CreateAttribute<FloatWrapper>(name);
    else if (type == "bool")
        is_valid_name = item->CreateAttribute<BoolWrapper>(name);
    else if (type == "string")
        is_valid_name = item->CreateAttribute<StringWrapper>(name);
    else if (type == "vec2")
        is_valid_name = item->CreateAttribute<Vector2Wrapper>(name);
    else if (type == "vec4")
        is_valid_name = item->CreateAttribute<Vector4Wrapper>(name);
    else
        throw InvalidAttributeType(node.type);

    if (!is_valid_name)
        throw AttributeAlreadyDefined(node.name);
}

void Interpreter::AssignAttribute(AttributeInterface& attribute,
                                  const ValueNode& value_node)
{
    // Reset the attribute to make sure that it is not
    // referencing any other attribute
    attribute.Reset();

    bool result = false;
    switch (value_node.type)
    {
    case ValueType::kString:
        result = attribute.LoadValue(
            dynamic_cast<const StringNode&>(value_node).value);
        break;
    case ValueType::kInt:
        result = attribute.LoadValue(
            dynamic_cast<const IntNode&>(value_node).value);
        break;
    case ValueType::kFloat:
        result = attribute.LoadValue(
            dynamic_cast<const FloatNode&>(value_node).value);
        break;
    case ValueType::kBool:
        result = attribute.LoadValue(
            dynamic_cast<const BoolNode&>(value_node).value);
        break;
    case ValueType::kVector2:
    {
        bt::Vector2 vec = this->EvalVector2Node(
            dynamic_cast<const Vector2Node&>(value_node));
        result = attribute.LoadValue(vec);
        break;
    }
    case ValueType::kVector4:
    {
        bt::Vector4 vec = this->EvalVector4Node(
            dynamic_cast<const Vector4Node&>(value_node));
        result = attribute.LoadValue(vec);
        break;
    }
    case ValueType::kAttributeAccess:
    {
        AttributeAccessNode& node = (AttributeAccessNode&)value_node;
        AttributeInterface* access = this->EvalAttributeAccessNode(node);

        if (node.by_reference)
        {
            result = attribute.InitReference(*access);
            break;
        }

        result = attribute.LoadValue(*access);
        break;
    }
    default:
        throw InternalError(value_node.value_token);
    }

    if (!result)
        throw UnableToConvertValue(value_node.value_token, attribute.GetName());
}

bt::Vector2 Interpreter::EvalVector2Node(const Vector2Node& value)
{
    FloatWrapper x, y;

    this->AssignAttribute((AttributeInterface&)x, std::move(*value.x.get()));
    this->AssignAttribute((AttributeInterface&)y, std::move(*value.y.get()));

    return bt::Vector2(x, y);
}

bt::Vector4 Interpreter::EvalVector4Node(const Vector4Node& value)
{
    FloatWrapper x, y, z, w;

    this->AssignAttribute((AttributeInterface&)x, std::move(*value.x.get()));
    this->AssignAttribute((AttributeInterface&)y, std::move(*value.y.get()));
    this->AssignAttribute((AttributeInterface&)z, std::move(*value.z.get()));
    this->AssignAttribute((AttributeInterface&)w, std::move(*value.w.get()));

    return bt::Vector4(x, y, z, w);
}

AttributeInterface* Interpreter::EvalAttributeAccessNode(
    const AttributeAccessNode& value)
{
    return this->GetAttributeFromFullID(value.name);
}

std::string Interpreter::GetCurrentID() const noexcept
{
    std::string full_id;

    for (const auto& item : this->item_stack_)
    {
        const std::string id = item->GetAccessID();

        if (id.empty())
            continue;

        if (!full_id.empty())
            full_id += '.';

        full_id += id;
    }

    return full_id;
}

AttributeInterface* Interpreter::GetAttributeFromCurrentItem(
    const Lexer::Token& token)
{
    if (this->item_stack_.empty())
        throw AttributeFromGlobalScope(token);

    const std::string& name = token.value;

    std::vector<std::string> segments = utils::SplitString(name, '.');

    if (segments.empty())
        throw InvalidAccessID(token);

    // Getting the front segment as child attributes may be set
    std::string attribute_name = segments.front();
    segments.erase(segments.begin());

    ItemBase* item = this->item_stack_.back();
    AttributeInterface* attribute = item->GetAttribute(attribute_name);

    if (attribute == nullptr)
        throw AttributeNotDefined(token, attribute_name);

    // No child attribute is defined if the segments are empty at this point
    if (segments.empty())
        return attribute;

    // We currently only expect that one child attribute is set.
    // Something like attribute.child.child is currently not supported.
    std::string child_attribute = segments.front();
    segments.erase(segments.begin());

    AttributeInterface* child = this->GetChildFromAttribute(
        attribute, attribute_name, child_attribute, token);

    if (segments.empty())
        return child;

    // There are multiple child attributes set if we get to this point.
    // We will throw the AttributeChildNotDefined exception because we know
    // for sure that there is currently no child attribute that can
    // contain another child.
    throw AttributeChildNotDefined(token, child_attribute, segments.front());
}

AttributeInterface* Interpreter::GetAttributeFromFullID(
    const Lexer::Token& token)
{
    const std::string& name = token.value;

    std::vector<std::string> segments = utils::SplitString(name, '.');

    if (segments.empty())
        throw InvalidAccessID(token);

    // Gets the item ID from the segments by iterating the segments from
    // the front and checking with each segment if there is any item
    // with the ID.
    // For example: root_item.item.attribute -> root_item.item
    std::string item_id;
    while (!segments.empty())
    {
        const std::string segment = segments.front();

        // Only add '.' to the next ID if its not empty.
        const std::string next_id = item_id +
            (item_id.empty() ? segment : '.' + segment);

        if (this->unit_.item_ids.find(next_id) == this->unit_.item_ids.end())
            break;

        item_id = next_id;
        segments.erase(segments.begin());
    }

    if (this->unit_.item_ids.find(item_id) == this->unit_.item_ids.end())
        throw UnableToFindItem(token);

    if (segments.empty())
        throw ItemReferenceNotSupported(token);

    // Expecting the attribute name at the front of the segments now;
    // item ID is erased from the segments.
    std::string attribute_name = segments.front();
    segments.erase(segments.begin());

    ItemBase* item = this->unit_.item_ids.at(item_id);
    AttributeInterface* attribute = item->GetAttribute(attribute_name);

    if (attribute == nullptr)
        throw AttributeNotDefined(token, item_id, attribute_name);

    // No child attribute is defined if the segments are empty at this point
    if (segments.empty())
        return attribute;

    // We currently only expect that one child attribute is set.
    // Something like attribute.child.child is currently not supported.
    std::string child_attribute = segments.front();
    segments.erase(segments.begin());

    AttributeInterface* child = this->GetChildFromAttribute(
        attribute, attribute_name, child_attribute, token);

    if (segments.empty())
        return child;

    // There are multiple child attributes set if we get to this point.
    // We will throw the AttributeChildNotDefined exception because we know
    // for sure that there is currently no child attribute that can
    // contain another child.
    throw AttributeChildNotDefined(token, child_attribute, segments.front());
}

AttributeInterface* Interpreter::GetChildFromAttribute(
    AttributeInterface* attribute, const std::string attribute_name,
    const std::string& child_name, const Lexer::Token& token)
{
    AttributeInterface* child = attribute->GetChildAttribute(child_name);

    if (!child)
        throw AttributeChildNotDefined(token, attribute_name, child_name);

    return child;
}

}  // namespace igm::internal
