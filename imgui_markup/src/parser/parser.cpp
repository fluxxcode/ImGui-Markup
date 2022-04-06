#include "impch.h"
#include "parser/parser.h"

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
    // TODO: Implementation
}


void Parser::ProcessAttributeCreate(const Lexer::Token& token)
{
    // TODO: Implementation
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
