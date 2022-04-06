#ifndef IMGUI_MARKUP_SRC_PARSER_PARSER_H_
#define IMGUI_MARKUP_SRC_PARSER_PARSER_H_

#include "parser/lexer.h"
#include "parser/interpreter.h"
#include "common/unit_stack.h"

namespace igm::internal
{

class Parser
{
public:
    Parser(Unit& dest);

    void ParseFromFile(std::string file);

private:
    Lexer lexer_;
    Interpreter interpreter_;

    void Reset() noexcept;

    inline bool IsItemDefinition(const Lexer::Token& token);
    inline bool IsItemBreak(const Lexer::Token& token);
    inline bool IsAttributeAssign(const Lexer::Token& token);
    inline bool IsAttributeCreate(const Lexer::Token& token);
    inline bool IsAttributeAccess(const Lexer::Token& token);
    inline bool IsAccessByValue(const Lexer::Token& token);
    inline bool IsAccessByReference(const Lexer::Token& token);
    inline bool IsString(const Lexer::Token& token);
    inline bool IsInt(const Lexer::Token& token);
    inline bool IsFloat(const Lexer::Token& token);
    inline bool IsBool(const Lexer::Token& token);
    inline bool IsVector(const Lexer::Token& token);

    void ProcessItemDefinition(const Lexer::Token& token);
    void ProcessItemBreak(const Lexer::Token& token);
    void ProcessAttributeAssign(const Lexer::Token& token);
    void ProcessAttributeCreate(const Lexer::Token& token);

    void ProcessTokens();

    Interpreter::ValueNode CreateValueNode(const Lexer::Token& token);
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

}  // namespace igm::internal

#endif  // IMGUI_MARKUP_SRC_PARSER_PARSER_H_
