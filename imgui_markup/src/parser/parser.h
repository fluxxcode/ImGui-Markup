#ifndef IMGUI_MARKUP_SRC_PARSER_PARSER_H_
#define IMGUI_MARKUP_SRC_PARSER_PARSER_H_

#include "parser/lexer.h"

namespace igm::internal
{

class Parser
{
public:
    void ParseFromFile(std::string file);

private:
    Lexer lexer_;

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

}  // namespace igm::internal

#endif  // IMGUI_MARKUP_SRC_PARSER_PARSER_H_
