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

    // TODO: Ability to access child attributes from a vector. E.g. vec.x, vec.y

    throw AttributeChildReferenceNotSupported(token);
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

    // TODO: Ability to access child attributes from a vector. E.g. vec.x, vec.y

    throw AttributeChildReferenceNotSupported(token);
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

}  // namespace igm::internal
