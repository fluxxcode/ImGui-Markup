#include "impch.h"
#include "parser/interpreter.h"

#include "items/item_factory.h"

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
