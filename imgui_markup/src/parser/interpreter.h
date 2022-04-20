#ifndef IMGUI_MARKUP_SRC_PARSER_INTERPRETER_H_
#define IMGUI_MARKUP_SRC_PARSER_INTERPRETER_H_

#include "common/unit_stack.h"
#include "parser/lexer.h"

namespace igm::internal
{

class Interpreter
{
public:
    enum class ValueType : unsigned char
    {
        kString,
        kInt,
        kFloat,
        kBool,
        kVector2,
        kVector4,
        kAttributeAccess
    };

    class ValueNode
    {
    public:
        const ValueType type;
        const Lexer::Token value_token;

        virtual ~ValueNode() { }

    protected:
        ValueNode(ValueType type, Lexer::Token value_token)
            : type(type), value_token(value_token)
        { }
    };

    struct StringNode : public ValueNode
    {
        StringNode(std::string value, Lexer::Token value_token)
            : ValueNode(ValueType::kString, value_token),
            value(value)
        { }
        ~StringNode() { }

        const std::string value;
    };

    struct IntNode : public ValueNode
    {
        IntNode(int value, Lexer::Token value_token)
            : ValueNode(ValueType::kInt, value_token),
            value(value)
        { }
        ~IntNode() { }

        const int value;
    };

    struct FloatNode : public ValueNode
    {
        FloatNode(float value, Lexer::Token value_token)
            : ValueNode(ValueType::kFloat, value_token),
            value(value)
        { }

        const float value;
    };

    struct BoolNode : public ValueNode
    {
        BoolNode(bool value, Lexer::Token value_token)
            : ValueNode(ValueType::kBool, value_token),
            value(value)
        { }

        const bool value;
    };

    struct Vector2Node : public ValueNode
    {
        Vector2Node(std::unique_ptr<ValueNode> x,
                    std::unique_ptr<ValueNode> y,
                    Lexer::Token value_token)
            : ValueNode(ValueType::kVector2, value_token),
            x(std::move(x)), y(std::move(y))
        { }

        std::unique_ptr<ValueNode> x, y;
    };

    struct Vector4Node : public ValueNode
    {
        Vector4Node(std::unique_ptr<ValueNode> x,
                    std::unique_ptr<ValueNode> y,
                    std::unique_ptr<ValueNode> z,
                    std::unique_ptr<ValueNode> w,
                    Lexer::Token value_token)
            : ValueNode(ValueType::kVector4, value_token),
            x(std::move(x)), y(std::move(y)), z(std::move(z)), w(std::move(w))
        { }

        std::unique_ptr<ValueNode> x, y, z, w;
    };

    struct AttributeAccessNode : public ValueNode
    {
        AttributeAccessNode(Lexer::Token name, bool by_reference,
                            Lexer::Token value_token)
            : ValueNode(ValueType::kAttributeAccess, value_token),
            name(name), by_reference(by_reference)
        { }

        const Lexer::Token name;
        const bool by_reference;
    };

    struct AttributeAssignNode
    {
        AttributeAssignNode(Lexer::Token name, ValueNode& value)
            : name(name), value(value)
        { }

        const Lexer::Token name;
        const ValueNode& value;
    };

    struct AttributeCreateNode
    {
        AttributeCreateNode(Lexer::Token name, ValueNode& value)
            : name(name), value(value)
        { }

        const Lexer::Token name;
        const ValueNode& value;
    };

    Interpreter(Unit& dest);

    void Reset() noexcept;

    void CreateItem(const Lexer::Token& type, const Lexer::Token& id);
    void PopItem(const Lexer::Token& token);

    void ProcessAssignAttributeNode(AttributeAssignNode node);
    void ProcessAttributeCreateNode(AttributeCreateNode node);

private:
    // Main destination buffer
    Unit& unit_;

    // Stack of the current proccessed items. Top of the stack is
    // the current item that is beeing proccessed.
    std::vector<ItemBase*> item_stack_;

    /**
     * Returns the full id of the object that is currently at the top
     * of the item stack.
     */
    std::string GetCurrentID() const noexcept;

    // Attribute from current processed object
    AttributeInterface* GetAttributeFromCurrentItem(const Lexer::Token& name);

    // Attribute from an object with full ID
    AttributeInterface* GetAttribute(const Lexer::Token& name);

    // Child attribute from an attribute
    AttributeInterface* GetChildFromAttribute(
        AttributeInterface* attribute, const std::string attribute_name,
        const std::string& child_name, const Lexer::Token& token);

    void AssignAttribute(AttributeInterface& attribute,
                         const ValueNode& value_node);

    Vector2 EvalVector2Node(const Vector2Node& value);
    Vector4 EvalVector4Node(const Vector4Node& value);
    AttributeInterface* EvalAttributeAccessNode(
        const AttributeAccessNode& value);
};

struct InterpreterException
{
    InterpreterException(std::string message, Lexer::Token token)
        : message(message), token(token)
    { }

    const std::string message;
    const Lexer::Token token;
};

struct InternalError : public InterpreterException
{
    InternalError(Lexer::Token token)
        : InterpreterException("INTERNAL_ERROR", token)
    { }
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

struct InvalidCharacterInID : public InterpreterException
{
    InvalidCharacterInID(Lexer::Token token, const char c)
        : InterpreterException("'" + std::string(1, c) +
                               "' in item ID is not allowed", token)
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
        : InterpreterException("Unable to access an attribute from the global "
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

struct AttributeChildNotDefined : public InterpreterException
{
    AttributeChildNotDefined(Lexer::Token token, std::string attribute,
                             std::string child)
        : InterpreterException("Attribute \"" + attribute + "\" has no child "
                               "attribute called \"" + child + "\"", token)
    { }
};

struct UnableToConvertValue : public InterpreterException
{
    // TODO: Improve error message by specifing type
    UnableToConvertValue(Lexer::Token token)
        : InterpreterException("Unable to convert value", token)
    { }
};

}  // namespace igm::internal

#endif  // IMGUI_MARKUP_SRC_PARSER_INTERPRETER_H_
