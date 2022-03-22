#ifndef IMGUI_MARKUP_SRC_PARSER_LEXER_H_
#define IMGUI_MARKUP_SRC_PARSER_LEXER_H_

namespace igm::internal
{

class Lexer
{
public:
    enum class TokenType : unsigned char
    {
        kUndefined,
        kColon,         // :
        kComma,         // ,
        kEqual,         // =
        kPlus,          // +
        kAt,            // @
        kBracketOpen,   // (
        kBracketClose,  // )
        kCurlyOpen,     // {
        kCurlyClose,    // }
        kString,        // "text"
        kInt,           // 1234
        kFloat,         // 1234.5678
        kBool,          // true/false
        kKeyword,       // Words containing alphabetical, numerican characters,
                        // '_' and '.'
                        // Keywords can't start with '.' or an number.
        kEndOfFile      // End of file
    };

    struct TokenPosition
    {
        TokenPosition(std::string line, size_t line_number,
                      size_t start, size_t end)
            : line(line), line_number(line_number), start(start), end(end)
        { }

        std::string line;
        size_t line_number;
        size_t start;
        size_t end;
    };

    struct Token
    {
        Token (TokenType type, std::string line, size_t line_number,
               size_t start, size_t end, std::string value = "")
            : type(type), value(value),
              position(TokenPosition(line, line_number, start, end))
        { }

        TokenType type;
        std::string value;
        TokenPosition position;
    };

    struct FileContext
    {
        std::string path;
        size_t position = 0;  // Position in the current line
        size_t line_number = 1;
        std::string current_line;
    };

    void LoadFromFile(std::string path);

    Lexer::Token Get();
    Lexer::Token Peek();

    void Reset() noexcept;

private:
    struct File
    {
        FileContext context;
        std::ifstream fstream;
    };
    std::vector<File> file_stack_;

    std::vector<Token> token_cache_;

    void OpenFile(std::string path, Token token);
    void PopFile() noexcept;
    bool IsFileInFileStack(std::string path) const noexcept;

    char GetChar() noexcept;
    char PeekChar() noexcept;

    inline std::string GetCurrentDirectory() const noexcept;
    inline std::string GetCurrentLine() const noexcept;
    inline size_t GetCurrentLineNumber() const noexcept;
    inline size_t GetCurrentPosition() const noexcept;

    Token ConstructToken(TokenType type) const noexcept;
    Token ConstructToken(TokenType type, std::string value,
                         int offset_l = 0,
                         int offset_r = 0) const noexcept;

    bool SkipComment(char c) noexcept;
    void SkipWhiteSpace() noexcept;

    std::string ParseString();
    Token CreateString();

    bool IsNumber(char c) const noexcept;
    Token CreateNumber(char c);

    bool IsKeyword(char c) const noexcept;
    Token CreateKeyword(char c);

    Token GenerateToken();

    Token ParseInstruction();

    Token ExecuteIncludeInstruction();

    void LexerInstructionInclude();
};

struct LexerException
{
    LexerException(std::string message, Lexer::Token token)
        : message(message), token(token)
    { }

    const std::string message;
    const Lexer::Token token;
};

struct UnableToOpenFile : public LexerException
{
    UnableToOpenFile(Lexer::Token token)
        : LexerException("Unable to open file", token)
    { }
};

struct FileIncludesItself : public LexerException
{
    FileIncludesItself(Lexer::Token token)
        : LexerException("File includes itself", token)
    { }
};

struct InvalidSymbol : public LexerException
{
    InvalidSymbol(Lexer::Token token)
        : LexerException("Invalid symbol", token)
    { }
};

struct UnexpectedEndOfFile : public LexerException
{
    UnexpectedEndOfFile(Lexer::Token token)
        : LexerException("Unexpected end of file", token)
    { }
};

struct UnexpectedSequenceOfTokens : public LexerException
{
    UnexpectedSequenceOfTokens(Lexer::Token token)
        : LexerException("Undefined sequence of tokens", token)
    { }
};

struct UnknownLexerInstruction : public LexerException
{
    UnknownLexerInstruction(Lexer::Token token)
        : LexerException("Unknown lexer instruction", token)
    { }
};

struct WrongIncludeArgument : public LexerException
{
    WrongIncludeArgument(Lexer::Token token)
        : LexerException("Expecting string after include instruction", token)
    { }
};

}  // namespace igm::internal

#endif  // IMGUI_MARKUP_SRC_PARSER_LEXER_H_
