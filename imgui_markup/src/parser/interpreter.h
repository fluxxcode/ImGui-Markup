#ifndef IMGUI_MARKUP_SRC_PARSER_INTERPRETER_H_
#define IMGUI_MARKUP_SRC_PARSER_INTERPRETER_H_

#include "common/unit_stack.h"
#include "parser/lexer.h"

namespace igm::internal
{

class Interpreter
{
public:
    Interpreter(Unit& dest);

    void Reset() noexcept;

    void CreateItem(const Lexer::Token& type, const Lexer::Token& id);
    void PopItem(const Lexer::Token& token);

private:
    // Main destination buffer
    Unit& unit_;

    // Stack of the current proccessed items. Top of the stack is
    // the current item that is beeing proccessed.
    std::vector<ItemBase*> item_stack_;

    /**
     * Returns the full id of the objects thats currently at the top
     * of the item stack.
     */
    std::string GetCurrentID() const noexcept;
};

struct InterpreterException
{
    InterpreterException(std::string message, Lexer::Token token)
        : message(message), token(token)
    { }

    const std::string message;
    const Lexer::Token token;
};

struct ExpectedItemDeclaration : public InterpreterException
{
    ExpectedItemDeclaration(Lexer::Token token)
        : InterpreterException("Expected item declaration", token)
    { }
};

struct UndefinedItemType : public InterpreterException
{
    UndefinedItemType(Lexer::Token token)
        : InterpreterException("Undefined item type", token)
    { }
};

struct IDIsAlreadyDefined : public InterpreterException
{
    IDIsAlreadyDefined(Lexer::Token token)
        : InterpreterException("ID is already defiend", token)
    { }
};

}  // namespace igm::internal

#endif  // IMGUI_MARKUP_SRC_PARSER_INTERPRETER_H_
