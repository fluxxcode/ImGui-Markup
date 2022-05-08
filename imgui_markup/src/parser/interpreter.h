#ifndef IMGUI_MARKUP_SRC_PARSER_INTERPRETER_H_
#define IMGUI_MARKUP_SRC_PARSER_INTERPRETER_H_

/**
 * @file interpreter.h
 * @author FluxxCode (info.fluxxcode@gmail.com)
 * @brief Contains the main interpreter for the markup language.
 * @copyright Copyright (c) 2022
 */

#include "common/unit_stack.h"
#include "parser/lexer.h"
#include "attribute_types/attribute_base.h"
#include "attribute_types/internal_vector.h"
#include "attribute_types/float_wrapper.h"
#include "attribute_types/int_wrapper.h"
#include "attribute_types/string_wrapper.h"
#include "attribute_types/bool_wrapper.h"

namespace igm::internal
{

/**
 * Main interpreter that is used for the markup language.
 * It is designed to work together with the parser, not as a standalone class.
 * Unlike many other interpreters that process a ready-made tree,
 * this one processes individual nodes right after they have been
 * created by the parser; no tree is created during the whole parsing process.
 * Also manages the destination unit.
 */
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

        const StringWrapper value;
    };

    struct IntNode : public ValueNode
    {
        IntNode(int value, Lexer::Token value_token)
            : ValueNode(ValueType::kInt, value_token),
            value(value)
        { }
        ~IntNode() { }

        const IntWrapper value;
    };

    struct FloatNode : public ValueNode
    {
        FloatNode(float value, Lexer::Token value_token)
            : ValueNode(ValueType::kFloat, value_token),
            value(value)
        { }

        const FloatWrapper value;
    };

    struct BoolNode : public ValueNode
    {
        BoolNode(bool value, Lexer::Token value_token)
            : ValueNode(ValueType::kBool, value_token),
            value(value)
        { }

        const BoolWrapper value;
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
        AttributeCreateNode(Lexer::Token type, Lexer::Token name)
            : type(type), name(name)
        { }

        const Lexer::Token type;
        const Lexer::Token name;
    };

    Interpreter(Unit& dest);

    /**
     * Resets the entire interpreter, including the destination unit.
     */
    void Reset() noexcept;

    /**
     * @brief Creates a new item within the item that is currently on the
     *        top of the item stack. Pushes the new item to the top of the
     *        item stack afterwads.
     *
     * @param type - Lexer token of type keyword, with the type of the
     *               desired item as the token's value.
     *               Type of the item has to be defined within the item factory.
     *               See items/item_factory.h for more details.

     * @param id  - Lexer token with the ID of the new item as the
     *              token's value. An empty string indicates that the
     *              item has no ID.
     *              The function only expects the ID of the item and not the
     *              full ID. The full ID will be generated by the
     *              function itself using the item stack.
     *
     * @throws InvalidCharacterInID when the ID contains a '.'.
     *         UndefinedItemType when the type of the item is not defined
     *              within the item factory.
     *         IDIsAlreadyDefined when there already exists an item with the
     *              desired ID.
     */
    void CreateItem(const Lexer::Token& type, const Lexer::Token& id);

    /**
     * Pops the item that is currently on the top of the item stack.
     * This function is called by the parser when an item is finished
     * processing, indicated by a '}' within the markup language.
     *
     * @param token - Token of the '}', only used for error messages.
     *
     * @throws ExpectedItemDeclaration when the item stack is empty and the
     *              '}' is within the global scope of the unit.
     */
    void PopItem(const Lexer::Token& token);

    /**
     * Processes an AttributeAssignNode, evaluates the value and assigns
     * it to the given attribute from the item that is currently
     * on the top of the item stack.
     *
     * @throws AttributeFromGlobalScope when the item stack is empty
     *             and an attempt is made to get an attribute from the
     *             global scope.
     *         InvalidAccessID when the given ID is invalid and does
     *             not contain any segments.
     *         AttributeNotDefined when the specific attribute does not exists.
     *         AttributeChildNotDefined when a child attribute is given
     *             that does not exists.
     *        InternalError when a value type is given that is not implemented,
     *             indicates an internal bug.
     *         UnableToConvertValue when the given value type cannot by
     *              converted to the type of the given attribute.
     */
    void ProcessAssignAttributeNode(AttributeAssignNode node);

    /**
     * Processes an AttribtueCreateNode, evaluates the value and creates
     * a new attribute within the item that is on top of the item stack.
     *
     * @throws CreateAttributeInGlobalScope when the item stack is empty
     *             and an attempt is made to get create an attribute within the
     *             global scope.
     *         ExpectingValue when the value is not of type string, int,
     *              float, bool, vector2 or vector4.
     *         AttributeAlreadyDefined when the item already has an
     *              attribute with the given name.
     */
    void ProcessAttributeCreateNode(AttributeCreateNode node);

private:
    /**
     * Main destination unit, set within the constructor.
     */
    Unit& unit_;

    /**
     * Main stack of the current processed items. The top of the stack is
     * always the currently processed item. Items before the
     * top item are its child items.
     */
    std::vector<ItemBase*> item_stack_;

    /**
     * Returns the full id of the currently processed item that is on
     * top of the item stack.
     */
    std::string GetCurrentID() const noexcept;

    /**
     * Get's an attribute interface from the item that is currently
     * processed and on the top of the item stack.
     *
     * @param name - Token with the attribute name as the token's value.
     *               The function expects the name of the attribute,
     *               not the full ID.
     *
     * @return Pointer to the curresponding attribute.
     *
     * @throws AttributeFromGlobalScope when the item stack is empty
     *             and an attempt is made to get an attribute from the
     *             global scope.
     *         InvalidAccessID when the given ID is invalid and does
     *             not contain any segments.
     *         AttributeNotDefined when the specific attribute does not exists.
     *         AttributeChildNotDefined when a child attribute is given
     *             that does not exists.
     */
    AttributeInterface* GetAttributeFromCurrentItem(const Lexer::Token& name);

    /**
     * Get's an attribute interface from a full ID.
     * Example:
     * root_item.parent_item.parent_item.item.attribute
     *
     * @param name - Token with the attribute's full ID as the token's value.
     *
     * @return Pointer to the curresponding attribute.
     *
     * @throws InvalidAccessID when the given ID is invalid and does
     *             not contain any segments.
     *         UnableToFindItem when the given item does not exists.
     *         ItemReferenceNotSupported when an attempt is made to reference
     *              an item instead of an attribute.
     *         AttributeNotDefined when the specific attribute does not exists.
     *         AttributeChildNotDefined when a child attribute is given
     *             that does not exists.
     */
    AttributeInterface* GetAttributeFromFullID(const Lexer::Token& name);

    /**
     * Get's a child attribute from another attribute.
     * This currently only comprise child attributes from a vector.
     * For example vector.x or vector.y
     *
     * NOTE: This system could be changed in the future and will probably move
     *       into the attribute classes themselves.
     *
     * @param attribute - Pointer to the parent attribute containing the
     *                    desired child attribute.
     * @param attribute_name - Name of the parent attribute,
     *                         currently only used for error messages.
     * @param child_name - Name of the desired child attribute.
     *                     For example x or y
     * @param token - Token used for error messages
     *
     * @return Pointer to the curresponding attribute.
     *
     * @throws AttributeChildNotDefined if the parent attribute does not have
     *              the desired child attribute.
     */
    AttributeInterface* GetChildFromAttribute(
        AttributeInterface* attribute, const std::string attribute_name,
        const std::string& child_name, const Lexer::Token& token);

    /**
     * Evaluates a value node and assigns it to a specific attribute
     *
     * @param attribute Reference to the attribute to which the value will be
     *                  assigned.
     * @param value_node Value node that is evaluated and assigned to the
     *                   given attribute.
     *
     * @throws InternalError when a value type is given that is not implemented,
     *             indicates an internal bug.
     *         UnableToConvertValue when the given value type cannot by
     *              converted to the type of the given attribute.
     */
    void AssignAttribute(AttributeInterface& attribute,
                         const ValueNode& value_node);

    InternalVector2 EvalVector2Node(const Vector2Node& value);
    InternalVector4 EvalVector4Node(const Vector4Node& value);
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

struct CreateAttributeInGlobalScope : public InterpreterException
{
    CreateAttributeInGlobalScope(Lexer::Token token)
        : InterpreterException("Unable to create an attribute within the "
                                "global scope; expecting item declaration",
                                token)
    { }
};

struct InvalidAccessID : public InterpreterException
{
    InvalidAccessID(Lexer::Token token)
        : InterpreterException("Invalid access ID", token)
    { }
};

struct UnableToFindItem : public InterpreterException
{
    UnableToFindItem(Lexer::Token token)
        : InterpreterException("Unable to find item with id: \"" +
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
    UnableToConvertValue(Lexer::Token token, AttributeType type)
        : InterpreterException("Value cannot be converted to a type of '" +
                               AttributeInterface::AttributeTypeToString(type) +
                               "'", token)
    { }
};

struct ExpectingValue : public InterpreterException
{
    ExpectingValue(Lexer::Token token)
        : InterpreterException("Expecting value", token)
    { }
};

struct InvalidAttributeType : public InterpreterException
{
    InvalidAttributeType(Lexer::Token token)
        : InterpreterException("Invalid attribute type", token)
    { }
};

struct AttributeAlreadyDefined : public InterpreterException
{
    AttributeAlreadyDefined(Lexer::Token token)
        : InterpreterException("Item already has an attribute with the name '" +
                               token.value + "'", token)
    { }
};

}  // namespace igm::internal

#endif  // IMGUI_MARKUP_SRC_PARSER_INTERPRETER_H_
