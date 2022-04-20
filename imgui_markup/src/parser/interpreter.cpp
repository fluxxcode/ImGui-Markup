#include "impch.h"
#include "parser/interpreter.h"

#include "items/item_factory.h"
#include "utility/utility.h"

namespace igm::internal
{

Interpreter::Interpreter(Unit& unit)
    : unit_(unit)
{ }

void Interpreter::Reset() noexcept
{
    this->unit_.item_tree.clear();
    this->unit_.item_ids.clear();
}

void Interpreter::CreateItem(const Lexer::Token& type, const Lexer::Token& id)
{
    if (id.value.find('.') != std::string::npos)
        throw InvalidCharacterInID(id, '.');

    ItemBase* new_item = nullptr;

    if (this->item_stack_.empty())
    {
        this->unit_.item_tree.push_back(
            ItemFactory::CreateItem(type.value, id.value, nullptr));

        new_item = this->unit_.item_tree.back().get();
    }
    else
    {
        new_item = this->item_stack_.back()->CreateChildItem(
            type.value, id.value);
    }

    if (new_item == nullptr)
        throw UndefinedItemType(type);

    this->item_stack_.push_back(new_item);

    if (id.value.empty())
        return;

    std::string full_id = this->GetCurrentID();

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
    AttributeInterface* attribute = this->GetAttributeFromCurrentItem(
        node.name);

    this->AssignAttribute(*attribute, node.value);
}

void Interpreter::AssignAttribute(AttributeInterface& attribute,
                                  const ValueNode& value_node)
{
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
        result = attribute.LoadValue(this->EvalVector2Node(
            dynamic_cast<const Vector2Node&>(value_node)));
        break;
    case ValueType::kVector4:
        result = attribute.LoadValue(this->EvalVector4Node(
            dynamic_cast<const Vector4Node&>(value_node)));
        break;
    case ValueType::kAttributeAccess:
        {
            AttributeAccessNode& node = (AttributeAccessNode&)value_node;
            AttributeInterface* access =this->EvalAttributeAccessNode(node);

            if (node.by_reference)
            {
                result = attribute.InitReference(*access);
                break;
            }

            result = attribute.LoadValue(access);
            break;
        }
    default:
        throw InternalError(value_node.value_token);
    }

    if (!result)
        throw UnableToConvertValue(value_node.value_token);
}

void Interpreter::ProcessAttributeCreateNode(
    Interpreter::AttributeCreateNode node)
{
    // TODO: Implementation
}

Vector2 Interpreter::EvalVector2Node(const Vector2Node& value)
{
    FloatWrapper x, y;

    this->AssignAttribute((AttributeInterface&)x, std::move(*value.x.get()));
    this->AssignAttribute((AttributeInterface&)y, std::move(*value.y.get()));

    return Vector2(x, y);
}

Vector4 Interpreter::EvalVector4Node(const Vector4Node& value)
{
    FloatWrapper x, y, z, w;

    this->AssignAttribute((AttributeInterface&)x, std::move(*value.x.get()));
    this->AssignAttribute((AttributeInterface&)y, std::move(*value.y.get()));
    this->AssignAttribute((AttributeInterface&)z, std::move(*value.z.get()));
    this->AssignAttribute((AttributeInterface&)w, std::move(*value.w.get()));

    return Vector4(x, y, z, w);
}

AttributeInterface* Interpreter::EvalAttributeAccessNode(
    const AttributeAccessNode& value)
{
    return this->GetAttribute(value.name);
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

    std::string attribute_name = segments.front();
    segments.erase(segments.begin());

    ItemBase* item = this->item_stack_.back();
    AttributeInterface* attribute = item->GetAttribute(attribute_name);

    if (attribute == nullptr)
        throw AttributeNotDefined(token, attribute_name);

    if (segments.empty())
        return attribute;

    std::string child_attribute = segments.front();
    segments.erase(segments.begin());

    AttributeInterface* child = this->GetChildFromAttribute(
        attribute, attribute_name, child_attribute, token);

    if (segments.empty())
        return child;

    throw AttributeChildNotDefined(token, child_attribute, segments.front());
}

AttributeInterface* Interpreter::GetAttribute(const Lexer::Token& token)
{
    const std::string& name = token.value;

    std::vector<std::string> segments = utils::SplitString(name, '.');

    if (segments.empty())
        throw InvalidAccessID(token);

    std::string item_id;
    while (!segments.empty())
    {
        const std::string segment = segments.front();

        const std::string next_id = item_id +
            (item_id.empty() ? segment : '.' + segment);

        if (this->unit_.item_ids.find(next_id) == this->unit_.item_ids.end())
            break;

        item_id = next_id;
        segments.erase(segments.begin());
    }

    if (this->unit_.item_ids.find(item_id) == this->unit_.item_ids.end())
        throw UnableToFindObject(token);

    if (segments.empty())
        throw ItemReferenceNotSupported(token);

    std::string attribute_name = segments.front();
    segments.erase(segments.begin());

    ItemBase* item = this->unit_.item_ids.at(item_id);
    AttributeInterface* attribute = item->GetAttribute(attribute_name);

    if (attribute == nullptr)
        throw AttributeNotDefined(token, item_id, attribute_name);

    if (segments.empty())
        return attribute;

    std::string child_attribute = segments.front();
    segments.erase(segments.begin());

    AttributeInterface* child = this->GetChildFromAttribute(
        attribute, attribute_name, child_attribute, token);

    if (segments.empty())
        return child;

    throw AttributeChildNotDefined(token, child_attribute, segments.front());
}

AttributeInterface* Interpreter::GetChildFromAttribute(
    AttributeInterface* attribute, const std::string attribute_name,
    const std::string& child_name, const Lexer::Token& token)
{
    if (attribute->GetType() == AttributeType::kVector2)
    {
        if (child_name == "x")
        {
            return (AttributeInterface*)&(
                ((Vector2Wrapper*)attribute)->GetValue().x);
        }
        if (child_name == "y")
        {
            return (AttributeInterface*)&(
                ((Vector2Wrapper*)attribute)->GetValue().y);
        }
    }
    else if (attribute->GetType() == AttributeType::kVector4)
    {
        if (child_name == "x")
        {
            return (AttributeInterface*)&(
                ((Vector4Wrapper*)attribute)->GetValue().x);
        }
        if (child_name == "y")
        {
            return (AttributeInterface*)&(
                ((Vector4Wrapper*)attribute)->GetValue().y);
        }
        if (child_name == "z")
        {
            return (AttributeInterface*)&(
                ((Vector4Wrapper*)attribute)->GetValue().z);
        }
        if (child_name == "w")
        {
            return (AttributeInterface*)&(
                ((Vector4Wrapper*)attribute)->GetValue().w);
        }
    }

    throw AttributeChildNotDefined(token, attribute_name, child_name);
}

}  // namespace igm::internal
