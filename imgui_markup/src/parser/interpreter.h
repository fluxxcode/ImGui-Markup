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

    // Attribute from current processed object
    AttributeInterface* GetAttributeFromCurrentItem(const Lexer::Token& name);

    // Attribute from an object with full ID
    AttributeInterface* GetAttribute(const Lexer::Token& name);

    void CreateAttribtue(std::string name, int value) noexcept;
    void CreateAttribtue(std::string name, float value) noexcept;
    void CreateAttribtue(std::string name, bool value) noexcept;
    void CreateAttribtue(std::string name, const char* value) noexcept;
    void CreateAttribtue(std::string name, Vector2 value) noexcept;
    void CreateAttribtue(std::string name, Vector4 value) noexcept;

private:
    // Main destination buffer
    Unit& unit_;

    // Stack of the current proccessed items. Top of the stack is
    // the current item that is beeing proccessed.
    std::vector<ItemBase*> item_stack_;

    /**
     * Returns the full id of the object that mis currently at the top
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

struct AttributeFromGlobalScope : public InterpreterException
{
    AttributeFromGlobalScope(Lexer::Token token)
        : InterpreterException("Unable to access an attribute form the global "
                               "scope", token)
    { }
};

struct InvalidAccessID : public InterpreterException
{
    InvalidAccessID(Lexer::Token token)
        : InterpreterException("Invalid access ID", token)
    { }
};

struct UnableToFindObject : public InterpreterException
{
    UnableToFindObject(Lexer::Token token)
        : InterpreterException("Unable to find object with id: \"" +
                               token.value + "\"", token)
    { }
};

struct ItemReferenceNotSupported : public InterpreterException
{
    ItemReferenceNotSupported(Lexer::Token token)
        : InterpreterException("Reference to an item is not supported", token)
    { }
};

struct AttributeNotDefined : public InterpreterException
{
    AttributeNotDefined(Lexer::Token token, std::string item,
                        std::string attribute)
    : InterpreterException("Item with ID \"" + item + "\" has no "
                           "attribute called \"" + attribute + "\"", token)
    { }

    AttributeNotDefined(Lexer::Token token, std::string attribute)
    : InterpreterException("Item has no attribute called \"" + attribute + "\"",
                           token)
    { }
};

struct AttributeChildReferenceNotSupported : public InterpreterException
{
    AttributeChildReferenceNotSupported(Lexer::Token token)
        : InterpreterException("Reference to a child of an attribute is "
                               "currently not supported", token)
    { }
};


}  // namespace igm::internal

#endif  // IMGUI_MARKUP_SRC_PARSER_INTERPRETER_H_
