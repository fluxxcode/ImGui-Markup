#include "impch.h"
#include "parser/parser.h"

/**
 * @file parser.cpp
 * @author FluxxCode (info.fluxxcode@gmail.com)
 * @brief Implementation of parser.h
 * @copyright Copyright (c) 2022
 */

#include "utility/utility.h"

namespace igm::internal
{

Parser::Parser(Unit& dest)
    : interpreter_(Interpreter(dest))
{ }

ParserResult Parser::ParseFromFile(std::string file)
{
    this->Reset();

    try
    {
        this->lexer_.InitFile(file);

        this->ProcessTokens();
    }
    catch (const LexerException& e)
    {
        this->interpreter_.Reset();  // Clear destination unit
        return ParserResult(ParserResultType::kError, e.message,
                            Parser::CreateParserPosition(e.token));

    }
    catch (const ParserException& e)
    {
        this->interpreter_.Reset();  // Clear destination unit
        return ParserResult(ParserResultType::kError, e.message,
                            Parser::CreateParserPosition(e.token));
    }
    catch (const InterpreterException& e)
    {
        this->interpreter_.Reset();  // Clear destination unit
        return ParserResult(ParserResultType::kError, e.message,
                            Parser::CreateParserPosition(e.token));
    }

    return ParserResult();  // -> will default to Success
}

void Parser::Reset() noexcept
{
    this->lexer_.Reset();
    this->interpreter_.Reset();
}

bool Parser::IsItemDefinition(const Lexer::Token& token)
{
    if (token.type != Lexer::TokenType::kKeyword)
        return false;

    const Lexer::TokenType next = this->lexer_.Peek().type;

    if (next == Lexer::TokenType::kColon ||
        next == Lexer::TokenType::kCurlyOpen)
    {
        return true;
    }

    return false;
}

bool Parser::IsItemBreak(const Lexer::Token& token)
{
    if (token.type == Lexer::TokenType::kCurlyClose)
        return true;

    return false;
}

bool Parser::IsAttributeAssign(const Lexer::Token& token)
{
    if (token.type != Lexer::TokenType::kKeyword)
        return false;

    if (this->lexer_.Peek().type == Lexer::TokenType::kEqual)
        return true;

    return false;
}

bool Parser::IsAttributeCreate(const Lexer::Token& token)
{
    if (token.type != Lexer::TokenType::kPlus)
        return false;

    if (this->lexer_.Peek().type == Lexer::TokenType::kKeyword)
        return true;

    return false;
}

bool Parser::IsAttributeAccess(const Lexer::Token& token)
{
    if (this->IsAccessByValue(token) || this->IsAccessByReference(token))
        return true;

    return false;
}

bool Parser::IsAccessByValue(const Lexer::Token& token)
{
    if (token.type == Lexer::TokenType::kKeyword)
        return true;

    return false;
}

bool Parser::IsAccessByReference(const Lexer::Token& token)
{
    if (token.type == Lexer::TokenType::kAt &&
        this->lexer_.Peek().type == Lexer::TokenType::kKeyword)
    {
        return true;
    }

    return false;
}

bool Parser::IsString(const Lexer::Token& token)
{
    if (token.type == Lexer::TokenType::kString)
        return true;

    return false;
}

bool Parser::IsInt(const Lexer::Token& token)
{
    if (token.type == Lexer::TokenType::kInt)
        return true;

    return false;
}

bool Parser::IsFloat(const Lexer::Token& token)
{
    if (token.type == Lexer::TokenType::kFloat)
        return true;

    return false;
}

bool Parser::IsBool(const Lexer::Token& token)
{
    if (token.type == Lexer::TokenType::kBool)
        return true;

    return false;
}

bool Parser::IsVector(const Lexer::Token& token)
{
    if (token.type == Lexer::TokenType::kBracketOpen)
        return true;

    return false;
}

std::unique_ptr<Interpreter::ValueNode> Parser::CreateString(
    const Lexer::Token& token)
{
    return std::make_unique<Interpreter::StringNode>(
        Interpreter::StringNode(token.value, token));
}

std::unique_ptr<Interpreter::ValueNode> Parser::CreateInt(
    const Lexer::Token& token)
{
    int temp;

    if (!utils::StringToInt(token.value, temp))
        throw UnableToConvertInt(token);

    return std::make_unique<Interpreter::IntNode>(
        Interpreter::IntNode(temp, token));
}

std::unique_ptr<Interpreter::ValueNode> Parser::CreateFloat(
    const Lexer::Token& token)
{
    float temp;

    if (!utils::StringToFloat(token.value, temp))
        throw UnableToConvertFloat(token);

    return std::make_unique<Interpreter::FloatNode>(
        Interpreter::FloatNode(temp, token));
}

std::unique_ptr<Interpreter::ValueNode> Parser::CreateBool(
    const Lexer::Token& token)
{
    bool temp;

    if (!utils::StringToBool(token.value, temp))
        throw UnableToConvertBool(token);

    return std::make_unique<Interpreter::BoolNode>(
        Interpreter::BoolNode(temp, token));
}

std::unique_ptr<Interpreter::ValueNode> Parser::CreateVector(
    const Lexer::Token& token)
{
    std::vector<std::unique_ptr<Interpreter::ValueNode>> values;

    while (this->lexer_.Peek().type != Lexer::TokenType::kEndOfFile)
    {
        values.push_back(this->CreateValueNode(this->lexer_.Get()));

        const Lexer::Token temp_token = this->lexer_.Get();

        if (temp_token.type == Lexer::TokenType::kBracketClose)
            break;

        if (temp_token.type != Lexer::TokenType::kComma)
            throw ExpectedComma(temp_token);
    }

    if (values.size() == 2)
    {
        return std::make_unique<Interpreter::Vector2Node>(
            Interpreter::Vector2Node(std::move(values[0]),
                                     std::move(values[1]),
                                     token));
    }
    else if (values.size() == 4)
    {
        return std::make_unique<Interpreter::Vector4Node>(
            Interpreter::Vector4Node(std::move(values[0]),
                                     std::move(values[1]),
                                     std::move(values[2]),
                                     std::move(values[3]),
                                     token));
    }

    throw UnexpectedNumberOfValuesInVector(token);
}

std::unique_ptr<Interpreter::ValueNode> Parser::CreateAttributeAccess(
    const Lexer::Token& token)
{
    Lexer::Token attribute_name = token;
    bool reference = false;

    if (this->IsAccessByReference(token))
    {
        reference = true;

        // Skip '@'
        attribute_name = this->lexer_.Get();
    }

    return std::make_unique<Interpreter::AttributeAccessNode>(
        Interpreter::AttributeAccessNode(attribute_name, reference,
                                         attribute_name));
}

std::unique_ptr<Interpreter::ValueNode> Parser::CreateValueNode(
    const Lexer::Token& token)
{
    if (this->IsString(token))
        return this->CreateString(token);
    else if (this->IsInt(token))
        return this->CreateInt(token);
    else if (this->IsFloat(token))
        return this->CreateFloat(token);
    else if (this->IsBool(token))
        return this->CreateBool(token);
    else if (this->IsVector(token))
        return this->CreateVector(token);
    else if (this->IsAttributeAccess(token))
        return this->CreateAttributeAccess(token);

    throw InvalidValue(token);
}

void Parser::ProcessItemDefinition(const Lexer::Token& token)
{
    Lexer::Token item_type = token;
    Lexer::Token item_id = Lexer::Token(Lexer::TokenType::kString, "", 0, 0, 0);

    Lexer::Token next = this->lexer_.Get();

    if (next.type == Lexer::TokenType::kColon)
    {
        item_id = this->lexer_.Get();

        if (this->lexer_.Peek().type != Lexer::TokenType::kCurlyOpen)
            throw ExpectedCurlyBracketOpen(token);

        this->lexer_.Get();
    }

    this->interpreter_.CreateItem(item_type, item_id);
}

void Parser::ProcessItemBreak(const Lexer::Token& token)
{
    this->interpreter_.PopItem(token);
}

void Parser::ProcessAttributeAssign(const Lexer::Token& token)
{
    // Skip '='
    this->lexer_.Get();

    std::unique_ptr<Interpreter::ValueNode> value = this->CreateValueNode(
        this->lexer_.Get());

    this->interpreter_.ProcessAssignAttributeNode(
        Interpreter::AttributeAssignNode(token, *value.get()));
}

void Parser::ProcessAttributeCreate(const Lexer::Token& token)
{
    // Skip '+'
    const Lexer::Token name = this->lexer_.Get();

    // Skip '='
    this->lexer_.Get();

    std::unique_ptr<Interpreter::ValueNode> value = this->CreateValueNode(
        this->lexer_.Get());

    this->interpreter_.ProcessAttributeCreateNode(
        Interpreter::AttributeCreateNode(name, *value.get()));
}

void Parser::ProcessTokens()
{
    while (this->lexer_.Peek().type != Lexer::TokenType::kEndOfFile)
    {
        const Lexer::Token token = this->lexer_.Get();

        if (this->IsItemDefinition(token))
            this->ProcessItemDefinition(token);
        else if (this->IsItemBreak(token))
            this->ProcessItemBreak(token);
        else if (this->IsAttributeAssign(token))
            this->ProcessAttributeAssign(token);
        else if (this->IsAttributeCreate(token))
            this->ProcessAttributeCreate(token);
        else
            throw UndefinedSequenceOfTokens(token);
    }
}

ParserPosition Parser::CreateParserPosition(Lexer::Token token) const
{
    return ParserPosition(this->lexer_.GetFileStack(), token.position.line,
                          token.position.line_number, token.position.start,
                          token.position.end);
}

}  // namespace igm::internal
