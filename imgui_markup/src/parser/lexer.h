#ifndef IMGUI_MARKUP_SRC_PARSER_LEXER_H_
#define IMGUI_MARKUP_SRC_PARSER_LEXER_H_

/**
 * @file lexer.h
 * @author FluxxCode (info.fluxxcode@gmail.com)
 * @brief Contains the main lexer for the markup language.
 * @copyright Copyright (c) 2022
 */

namespace igm::internal
{

/**
 * Main lexer that is used for the markup language.
 * It is designed to work together with the parser, not as a standalone class.
 * Unlike many other lexers that process all data at once, this one
 * only processes the next token when its needed by the parser.
 *
 * Currently the lexer can only process tokens from a file.
 * The process of raw strings might be added in the future.
 *
 * Current implemented lexer instructions:
 * - #include path(string) - Opens and includes a file given by the
 *                           path argument. Only paths relative to the
 *                           current file are allowed.
 */
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
        kKeyword,       // Words containing alphabetical, numeric characters,
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

    /**
     * Initializes the lexer to load tokens from a specific file.
     *
     * @param path - Relative or full path to the file.
     *
     * @throws UnableToOpenFile if the specified file cannot be opened.
     */
    void InitFile(std::string path);

    /**
     * Gets the next token and increments the position.
     *
     * @throws UnableToOpenFile when an include instruction is executed and
     *             the include file cannot be opened.
     *         InvalidSymbol when the lexer encounters an undefined symbol.
     *         UnexpectedEndOfFile when the lexer encounters the end of a file
     *                             while processing a string.
     *         UnknownLexerInstruction when an instruction is called
     *                                 that does not exist.
     *         WrongIncludeArgument when the argument of an include instruction
     *                              is not of type string.
     */
    Lexer::Token Get();

    /**
     * Gets the next token without incrementing the position.
     * So calling Peek multiple times will always return the same token.
     *
     * @throws UnableToOpenFile when an include instruction is executed and
     *             the include file cannot be opened.
     *         InvalidSymbol when the lexer encounters an undefined symbol.
     *         UnexpectedEndOfFile when the lexer encounters the end of a file
     *                             while processing a string.
     *         UnknownLexerInstruction when an instruction is called
     *                                 that does not exist.
     *         WrongIncludeArgument when the argument of an include instruction
     *                              is not of type string.
     */
    Lexer::Token Peek();

    /**
     * Gets the path of every file on the file stack.
     */
    std::vector<std::string> GetFileStack() const;

    /**
     * Resets the values within the lexer.
     */
    void Reset() noexcept;

private:
    struct File
    {
        FileContext context;
        std::ifstream fstream;
    };

    /**
     * Stack of the files that are currently processed.
     * Files are added to the stack when an include instruction is called.
     * The file on the top of the stack is always the main file
     * that is currently processed.
     */
    std::vector<File> file_stack_;

    /**
     * The token cache holds the tokens that where processed by the Peek()
     * function. The Get() function will use and delete the front of the cache
     * when its not empty.
     */
    std::vector<Token> token_cache_;

    /**
     * Opens a new file, creates the file context and adds it to the
     * file stack.
     *
     * @param path - Relative path to the file, full paths are not allowed.
     * @param token - Token of the path, generated by the include instruction.
     *                Only used for error messages.
     */
    void OpenFile(std::string path, Token token);

    /**
     * Pops the top of the file stack.
     */
    void PopFile() noexcept;

    /**
     * Checks if a given file is already in the file stack.
     * Used to make sure that files don't include each other, which
     * would result in an endless include loop.
     * This function expects the full path to the file. While only
     * relative paths are given to the lexer, their absolute paths are
     * stored within the file context.
     */
    bool IsFileInFileStack(std::string path) const noexcept;

    /**
     * Gets the next char within the current file and increments the position.
     * 0 is returned if there is no character left and the data is
     * finished processing.
     */
    char GetChar() noexcept;

    /**
     * Gets the next char within the current file without incrementing
     * the position.
     * 0 is returned if there is no character left and the data is
     * finished processing.
     */
    char PeekChar() noexcept;

    /**
     * Gets the directory of the file that is on the top of the file stack.
     * An empty string is returned if there is no file on the file stack.
     */
    inline std::string GetCurrentDirectory() const noexcept;

    /**
     * Gets a copy of the current processed line.
     * An empty string is returned if there is no file on the file stack.
     */
    inline std::string GetCurrentLine() const noexcept;

    /**
     * Gets the number of the current processed line, starting from 1.
     * 0 is returned if there is no file on the file stack.
     */
    inline size_t GetCurrentLineNumber() const noexcept;

    /**
     * Gets the position of the current char within the current line.
     * 0 is returned if there is no file on the file stack.
     */
    inline size_t GetCurrentPosition() const noexcept;

    /**
     * Constructs a token with an empty value.
     * Uses the current position.
     */
    Token ConstructToken(TokenType type) const noexcept;

    /**
     * Constructs a token with a specific value and calculates the values
     * position within the current line.
     * begin = current position - offset_l
     * end = current position + value.size + offset_r
     *
     * @param type - Type of the token that will be constructed
     * @param value - Value of the token
     * @param offset_l - Offset which will be subtracted from the
     *                   values begin position.
     * @param offset_r - Offset which will be added to the values end position.
     */
    Token ConstructToken(TokenType type, std::string value,
                         int offset_l = 0, int offset_r = 0) const noexcept;

    /**
     * Checks and skips one-line and multi-line comments.
     *
     * @param c - Current char that is being processed
     */
    bool SkipComment(char c) noexcept;

    /**
     * Skip whitespace from the current char.
     */
    void SkipWhiteSpace() noexcept;

    /**
     * Expects that the current char is the first value of a string.
     * Parses the string until the next '"'".
     */
    std::string ParseString();

    /**
     * Creates a string token and parses all strings that follow each other.
     * For example:
     *
     * "This is a string"
     * // Comment
     * "This is another string"
     *
     * Will be parsed as a single string:
     *
     * "This is a stringThis is another string"
     */
    Token CreateString();

    /**
     * Checks if the char is a digit, '.' or '-'.
     */
    bool IsNumber(char c) const noexcept;

    /**
     * Assumes that the current char that is given through the parameter
     * is the first char of the number.
     * Creates the curresponding token of type int or float.
     */
    Token CreateNumber(char c);

    /**
     * Checks if the current char that is given through the parameter is
     * the first char of a keyword.
     * Keywords contain alphabetical chars, numerical chars, '.' and  '_'.
     * Keywords are not allowed to start with a digit, since they will
     * be interpreted as numbers.
     */
    bool IsKeyword(char c) const noexcept;

    /**
     * Assumes that the current char that is given through the parameter
     * is the first char of a keyword.
     * Creates the curresponding keyword token.
     */
    Token CreateKeyword(char c);

    /**
     * Generates the next token.
     */
    Token GenerateToken();

    /**
     * Parses a lexer instruction, starting with '#'
     */
    Token ParseInstruction();

    /**
     * Executes the include instruction.
     * Opens and includes a file given by the path argument.
     * Only paths relative to the current file are allowed.
     */
    Token ExecuteIncludeInstruction();
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
