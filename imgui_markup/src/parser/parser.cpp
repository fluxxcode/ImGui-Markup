#include "impch.h"
#include "parser/parser.h"

#include "utility/utility.h"

namespace igm::internal
{

Parser::Parser(Unit& dest)
    : interpreter_(Interpreter(dest))
{ }

void Parser::ParseFromFile(std::string file)
{
    this->Reset();

    try
    {
        this->lexer_.LoadFromFile(file);

        this->ProcessTokens();
    }
    catch (const LexerException& e)
    {
        // TODO: Return error
        std::cerr << "ERROR: " + e.message << std::endl;
    }
    catch (const ParserException& e)
    {
        // TODO: Return error
        std::cerr << "ERROR: " + e.message << std::endl;
    }
    catch (const InterpreterException& e)
    {
        // TODO: Return error
        std::cerr << "ERROR: " + e.message << std::endl;
    }

    int a = 0;
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
    return std::make_unique<Interpreter::ValueNode>(
        Interpreter::StringNode(token.value, token));
}

std::unique_ptr<Interpreter::ValueNode> Parser::CreateInt(
    const Lexer::Token& token)
{
    int temp;

    if (!utils::StringToInt(token.value, temp))
        throw UnableToConvertInt(token);

    return std::make_unique<Interpreter::ValueNode>(
        Interpreter::IntNode(temp, token));
}

std::unique_ptr<Interpreter::ValueNode> Parser::CreateFloat(
    const Lexer::Token& token)
{
    float temp;

    if (!utils::StringToFloat(token.value, temp))
        throw UnableToConvertFloat(token);

    return std::make_unique<Interpreter::ValueNode>(
        Interpreter::FloatNode(temp, token));
}

std::unique_ptr<Interpreter::ValueNode> Parser::CreateBool(
    const Lexer::Token& token)
{
    bool temp;

    if (!utils::StringToBool(token.value, temp))
        throw UnableToConvertBool(token);

    return std::make_unique<Interpreter::ValueNode>(
        Interpreter::BoolNode(temp, token));
}

std::unique_ptr<Interpreter::ValueNode> Parser::CreateVector2(
    const Lexer::Token& x, const Lexer::Token& y, const Lexer::Token& token)
{
    return std::make_unique<Interpreter::ValueNode>(
        Interpreter::Vector2Node(*this->CreateValueNode(x).get(),
                                 *this->CreateValueNode(y).get(), token)
    );
}

std::unique_ptr<Interpreter::ValueNode> Parser::CreateVector4(
    const Lexer::Token& x, const Lexer::Token& y,
    const Lexer::Token& z, const Lexer::Token& w, const Lexer::Token& token)
{
    return std::make_unique<Interpreter::ValueNode>(
        Interpreter::Vector4Node(*this->CreateValueNode(x).get(),
                                 *this->CreateValueNode(y).get(),
                                 *this->CreateValueNode(z).get(),
                                 *this->CreateValueNode(w).get(), token)
    );
}

std::unique_ptr<Interpreter::ValueNode> Parser::CreateVector(
    const Lexer::Token& token)
{
    std::vector<Lexer::Token> values;

    size_t count = 0;
    while (this->lexer_.Peek().type != Lexer::TokenType::kBracketClose)
    {
        count++;
        const Lexer::Token value = this->lexer_.Get();

        if (count % 2 == 0)
        {
            if (value.type != Lexer::TokenType::kComma)
                throw ExpectedComma(value);

            continue;
        }

        values.push_back(value);
    }

    if (values.size() == 2)
        return this->CreateVector2(values[0], values[1], token);
    else if (values.size() == 4)
        return this->CreateVector4(values[0], values[1], values[2], values[3],
                                   token);

    throw UnexpectedNumberOfValuesInVector(token);
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

}  // namespace igm::internal
