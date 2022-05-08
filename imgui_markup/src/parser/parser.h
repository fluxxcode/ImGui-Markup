#ifndef IMGUI_MARKUP_SRC_PARSER_PARSER_H_
#define IMGUI_MARKUP_SRC_PARSER_PARSER_H_

/**
 * @file parser.h
 * @author FluxxCode (info.fluxxcode@gmail.com)
 * @brief Contains the main parser for the markup language.
 * @copyright Copyright (c) 2022
 */

#include "parser/lexer.h"
#include "parser/interpreter.h"
#include "common/unit_stack.h"
#include "parser/parser_result.h"

namespace igm::internal
{

/**
 * Main parser that is used for the markup language.
 * It is the 'root' of the parsing process and designed to work together
 * with the lexer and interpreter.
 */
class Parser
{
public:
    Parser(Unit& dest);

    ParserResult ParseFromFile(std::string file);

private:
    Lexer lexer_;
    Interpreter interpreter_;

    void Reset() noexcept;

    /**
     * Checks if the current token is the start of an item definition.
     * Following token combinations are possible:
     * - keyword, {    - If no item ID is set
     * - keyword, :    - If there is an item ID set
     *
     * @param token - Token that is currently processed
     * @throws LexerException; See lexer.h for more details.
     */
    inline bool IsItemDefinition(const Lexer::Token& token);

    /**
     * Checks if the current token is an item break.
     * Following token combinations are possible:
     * - }
     *
     * @param token - Token that is currently processed
     * @throws LexerException; See lexer.h for more details.
     */
    inline bool IsItemBreak(const Lexer::Token& token);

    /**
     * Checks if the current token is the start of an attribute assign node.
     * Following token combinations are possible:
     * - keyword, =
     *
     * @param token - Token that is currently processed
     * @throws LexerException; See lexer.h for more details.
     */
    inline bool IsAttributeAssign(const Lexer::Token& token);

    /**
     * Checks if the current token is the start of an attribute create node.
     * Following token combinations are possible:
     * - +, keyword
     *
     * @param token - Token that is currently processed
     * @throws LexerException; See lexer.h for more details.
     */
    inline bool IsAttributeCreate(const Lexer::Token& token);

    /**
     * Checks if the current token is the start of an attribute access node.
     * Following token combinations are possible:
     * - keyword       - If the attribtue's value is copied
     * - @, keyword    - If its a reference to the attribute
     *
     * @param token - Token that is currently processed
     * @throws LexerException; See lexer.h for more details.
     */
    inline bool IsAttributeAccess(const Lexer::Token& token);

    /**
     * Checks if the current token is the start of an attribute access by
     * value node.
     * Following token combinations are possible:
     * - keyword
     *
     * @param token - Token that is currently processed
     * @throws LexerException; See lexer.h for more details.
     */
    inline bool IsAccessByValue(const Lexer::Token& token);

    /**
     * Checks if the current token is the start of an attribute access by
     * reference node.
     * Following token combinations are possible:
     * - @, keyword
     *
     * @param token - Token that is currently processed
     * @throws LexerException; See lexer.h for more details.
     */
    inline bool IsAccessByReference(const Lexer::Token& token);

    /**
     * Checks if the current token is a string value.
     * Following token combinations are possible:
     * - string
     *
     * @param token - Token that is currently processed
     * @throws LexerException; See lexer.h for more details.
     */
    inline bool IsString(const Lexer::Token& token);

    /**
     * Checks if the current token is an int value.
     * Following token combinations are possible:
     * - int
     *
     * @param token - Token that is currently processed
     * @throws LexerException; See lexer.h for more details.
     */
    inline bool IsInt(const Lexer::Token& token);

    /**
     * Checks if the current token is a float value.
     * Following token combinations are possible:
     * - float
     *
     * @param token - Token that is currently processed
     * @throws LexerException; See lexer.h for more details.
     */
    inline bool IsFloat(const Lexer::Token& token);

    /**
     * Checks if the current token is a bool value.
     * Following token combinations are possible:
     * - bool
     *
     * @param token - Token that is currently processed
     * @throws LexerException; See lexer.h for more details.
     */
    inline bool IsBool(const Lexer::Token& token);

    /**
     * Checks if the current token is a vector value.
     * Following token combinations are possible:
     * - (
     *
     * @param token - Token that is currently processed
     * @throws LexerException; See lexer.h for more details.
     */
    inline bool IsVector(const Lexer::Token& token);

    std::unique_ptr<Interpreter::ValueNode> CreateString(
        const Lexer::Token& token);

    std::unique_ptr<Interpreter::ValueNode> CreateInt(
        const Lexer::Token& token);

    std::unique_ptr<Interpreter::ValueNode> CreateFloat(
        const Lexer::Token& token);

    std::unique_ptr<Interpreter::ValueNode> CreateBool(
        const Lexer::Token& token);

    std::unique_ptr<Interpreter::ValueNode> CreateVector(
        const Lexer::Token& token);

    std::unique_ptr<Interpreter::ValueNode> CreateAttributeAccess(
        const Lexer::Token& token);

    std::unique_ptr<Interpreter::ValueNode> CreateValueNode(
        const Lexer::Token& token);

    void ProcessItemDefinition(const Lexer::Token& token);
    void ProcessItemBreak(const Lexer::Token& token);
    void ProcessAttributeAssign(const Lexer::Token& token);
    void ProcessAttributeCreate(const Lexer::Token& token);

    void ProcessTokens();

    ParserPosition CreateParserPosition(Lexer::Token token) const;
};

struct ParserException
{
    ParserException(std::string message, Lexer::Token token)
        : message(message), token(token)
    { }

    const std::string message;
    const Lexer::Token token;
};

struct UndefinedSequenceOfTokens : public ParserException
{
    UndefinedSequenceOfTokens(Lexer::Token token)
        : ParserException("Undefined sequence of tokens", token)
    { }
};

struct ExpectedCurlyBracketOpen : public ParserException
{
    ExpectedCurlyBracketOpen(Lexer::Token token)
        : ParserException("Expected '{'", token)
    { }
};

struct ExpectedComma : public ParserException
{
    ExpectedComma(Lexer::Token token)
        : ParserException("Expected ','", token)
    { }
};

struct InvalidValue : public ParserException
{
    InvalidValue(Lexer::Token token)
        : ParserException("Expected value of type Int, Float, String, Bool, "
                          "Vec2, Vec4 or reference", token)
    { }
};

struct UnableToConvertInt : public ParserException
{
    UnableToConvertInt(Lexer::Token token)
        : ParserException("Unable to convert \"" + token.value + "\" to a "
                          "value of type Int", token)
    { }
};

struct UnableToConvertFloat : public ParserException
{
    UnableToConvertFloat(Lexer::Token token)
        : ParserException("Unable to convert \"" + token.value + "\" to a "
                          "value of type Float", token)
    { }
};

struct UnableToConvertBool : public ParserException
{
    UnableToConvertBool(Lexer::Token token)
        : ParserException("Unable to convert \"" + token.value + "\" to a "
                          "value of type Bool", token)
    { }
};

struct UnexpectedNumberOfValuesInVector : public ParserException
{
    UnexpectedNumberOfValuesInVector(Lexer::Token token)
        : ParserException("Unexpected number of values in vector", token)
    { }
};

struct ExpectedAttributeName : public ParserException
{
    ExpectedAttributeName(Lexer::Token token)
        : ParserException("Expected attribute name", token)
    { }
};

}  // namespace igm::internal

#endif  // IMGUI_MARKUP_SRC_PARSER_PARSER_H_
