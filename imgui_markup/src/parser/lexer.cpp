#include "impch.h"
#include "lexer.h"

/**
 * @file lexer.cpp
 * @author FluxxCode (info.fluxxcode@gmail.com)
 * @brief Implementation of lexer.h
 * @copyright Copyright (c) 2022
 */

namespace igm::internal
{

void Lexer::InitFile(std::string path)
{
    this->Reset();

    Token token(TokenType::kString, "", 0, 0, 0, path);
    this->OpenFile(path, token);
}

Lexer::Token Lexer::Get()
{
    Token token(TokenType::kEndOfFile, "", 0, 0, 0);

    if (!this->token_cache_.empty())
    {
        token = this->token_cache_.front();
        this->token_cache_.erase(this->token_cache_.begin());
        return token;
    }

    token = this->GenerateToken();

    return token;
}

Lexer::Token Lexer::Peek()
{
    if (this->token_cache_.empty())
        this->token_cache_.push_back(this->GenerateToken());

    return this->token_cache_.front();
}

std::vector<std::string> Lexer::GetFileStack() const
{
    std::vector<std::string> file_stack;

    for (const auto& file : this->file_stack_)
        file_stack.push_back(file.context.path);

    return file_stack;
}

void Lexer::Reset() noexcept
{
    while (this->file_stack_.size() != 0)
        this->PopFile();

    this->file_stack_.clear();
    this->token_cache_.clear();
}

void Lexer::OpenFile(std::string path, Token token)
{
    path = std::filesystem::absolute(path).string();

    if (this->IsFileInFileStack(path))
        throw FileIncludesItself(token);

    this->file_stack_.emplace_back(File());

    File& file = this->file_stack_.back();

    file.context.path = path;
    file.fstream.open(path);

    if (!file.fstream.is_open())
    {
        this->file_stack_.pop_back();
        throw UnableToOpenFile(token);
    }

    std::getline(file.fstream, file.context.current_line);
}

void Lexer::PopFile() noexcept
{
    this->file_stack_.back().fstream.close();
    this->file_stack_.pop_back();
}

bool Lexer::IsFileInFileStack(std::string path) const noexcept
{
    for (const auto& file : this->file_stack_)
    {
        if (std::filesystem::equivalent(file.context.path, path))
            return true;
    }

    return false;
}

char Lexer::GetChar() noexcept
{
    if (this->file_stack_.empty())
        return 0;

    File& file = this->file_stack_.back();

    // Check if the next char is on a new line
    if (file.context.position >= file.context.current_line.size())
    {
        file.context.position = 0;
        file.context.line_number++;

        if (!std::getline(file.fstream, file.context.current_line))
            // Pop the current file if there is no char left
            this->PopFile();

        return '\n';
    }

    return file.context.current_line[file.context.position++];;
}

char Lexer::PeekChar() noexcept
{
    if (this->file_stack_.empty())
        return 0;

    File& file = this->file_stack_.back();

    if (file.context.position >= file.context.current_line.size())
        return '\n';

    return file.context.current_line[file.context.position];
}

std::string Lexer::GetCurrentDirectory() const noexcept
{
    if (this->file_stack_.empty())
        return std::string();

    return std::filesystem::path(
        this->file_stack_.back().context.path).parent_path().string() + "/";
}

std::string Lexer::GetCurrentLine() const noexcept
{
    if (this->file_stack_.empty())
        return std::string();

    return this->file_stack_.back().context.current_line;
}

size_t Lexer::GetCurrentLineNumber() const noexcept
{
    if (this->file_stack_.empty())
        return 0;

    return this->file_stack_.back().context.line_number;
}

size_t Lexer::GetCurrentPosition() const noexcept
{
    if (this->file_stack_.empty())
        return 0;

    return this->file_stack_.back().context.position - 1;
}

Lexer::Token Lexer::ConstructToken(TokenType type) const noexcept
{
    const size_t pos = this->GetCurrentPosition();
    return Token(type, this->GetCurrentLine(), this->GetCurrentLineNumber(),
                 pos, pos);
}

Lexer::Token Lexer::ConstructToken(TokenType type, std::string value,
                                   int offset_l,
                                   int offset_r) const noexcept
{
    const size_t pos = this->GetCurrentPosition();
    return Token(type, this->GetCurrentLine(), this->GetCurrentLineNumber(),
                 pos - value.size() - offset_l, pos + offset_r, value);
}

bool Lexer::SkipComment(char c) noexcept
{
    const char next = this->PeekChar();

    if (c != '/')
        return false;

    if (next != '/' && next != '*')
        return false;

    // Oneline comments
    if (next == '/')
    {
        while (this->PeekChar() != '\n')
            this->GetChar();

        return true;
    }

    // Multiline comments
    char last = 0;
    char current = this->GetChar();
    while (true)
    {
        current = this->GetChar();

        if (current == 0)
            return true;

        if (current == '/' && last == '*')
            return true;

        last = current;
    }

    return false;
}

void Lexer::SkipWhiteSpace() noexcept
{
    while (std::isspace(this->PeekChar()) || this->PeekChar() == '/')
    {
        const char c = this->GetChar();

        if (std::isspace(c))
            continue;

        if (!this->SkipComment(c))
            break;
    }
}

std::string Lexer::ParseString()
{
    std::string data;

    char c = this->GetChar();

    if (c == '"')
        return std::string();

    while (true)
    {
        if (this->PeekChar() == '"' && c != '\\')
        {
            data += c;
            break;
        }
        if (c == 0)
        {
            throw UnexpectedEndOfFile(this->ConstructToken(TokenType::kString,
                                                           data));
        }
        if (c == '\\' && this->PeekChar() != '\\')
        {
            c = this->GetChar();
            continue;
        }

        data += c;

        c = this->GetChar();
    }

    // Skip '"'
    this->GetChar();

    return data;
}

Lexer::Token Lexer::CreateString()
{
    std::string data = this->ParseString();

    // TODO: Improve position and error message for strings that span over
    //       multiple lines

    const std::string line = this->GetCurrentLine();
    const size_t line_number = this->GetCurrentLineNumber();
    const size_t pos = this->GetCurrentPosition();

    this->SkipWhiteSpace();

    while (this->PeekChar() == '"')
    {
        this->GetChar();

        data += this->ParseString();

        this->SkipWhiteSpace();
    }

    return Token(TokenType::kString, line, line_number, pos - data.size() - 1,
                 pos, data);
}

bool Lexer::IsNumber(char c) const noexcept
{
    return std::isdigit(c) || c == '.' || c == '-';
}

Lexer::Token Lexer::CreateNumber(char c)
{
    std::string value(1, c);

    // Numbers starting with a '.' are interpreted as float numbers.
    // Make sure to increment the dot count
    size_t dot_count = c == '.' ? 1 : 0;

    while (this->IsNumber(this->PeekChar()))
    {
        const char c = this->GetChar();

        value += c;

        if (c == '.')
            dot_count++;
    }

    if (dot_count != 0)
        return this->ConstructToken(TokenType::kFloat, value, -1);

    return this->ConstructToken(TokenType::kInt, value, -1);
}

bool Lexer::IsKeyword(char c) const noexcept
{
    return std::isalpha(c) || std::isdigit(c) || c == '_' || c == '.';
}

Lexer::Token Lexer::CreateKeyword(char c)
{
    std::string value(1, c);

    while (this->IsKeyword(this->PeekChar()))
        value += this->GetChar();

    if (value == "true" || value == "false")
        return this->ConstructToken(TokenType::kBool, value, -1);

    return this->ConstructToken(TokenType::kKeyword, value, -1);
}

Lexer::Token Lexer::GenerateToken()
{
    char c = this->GetChar();

    if (this->SkipComment(c))
        return this->GenerateToken();

    if (c == 0)
        return this->ConstructToken(TokenType::kEndOfFile);

    if (std::isspace(c))
        return this->GenerateToken();
    else if (c == ':')
        return this->ConstructToken(TokenType::kColon);
    else if (c == ',')
        return this->ConstructToken(TokenType::kComma);
    else if (c == '=')
        return this->ConstructToken(TokenType::kEqual);
    else if (c == '+')
        return this->ConstructToken(TokenType::kPlus);
    else if (c == '@')
        return this->ConstructToken(TokenType::kAt);
    else if (c == '(')
        return this->ConstructToken(TokenType::kBracketOpen);
    else if (c == ')')
        return this->ConstructToken(TokenType::kBracketClose);
    else if (c == '{')
        return this->ConstructToken(TokenType::kCurlyOpen);
    else if (c == '}')
        return this->ConstructToken(TokenType::kCurlyClose);
    else if (c == '#')
        return this->ParseInstruction();
    else if (c == '"')
        return this->CreateString();
    else if (c == '-' || std::isdigit(c) || c == '.')
        return this->CreateNumber(c);
    else if (this->IsKeyword(c))
        return this->CreateKeyword(c);
    else
        throw InvalidSymbol(this->ConstructToken(TokenType::kUndefined,
                                                 std::string(1, c)));
}

Lexer::Token Lexer::ParseInstruction()
{
    std::string name;

    while(this->IsKeyword(this->PeekChar()))
        name += this->GetChar();

    if (name == "include")
        return this->ExecuteIncludeInstruction();

    throw UnknownLexerInstruction(this->ConstructToken(TokenType::kKeyword,
                                                       name));
}

Lexer::Token Lexer::ExecuteIncludeInstruction()
{
    Token arg = this->GenerateToken();

    if (arg.type != TokenType::kString)
        throw WrongIncludeArgument(arg);

    this->OpenFile(this->GetCurrentDirectory() + arg.value, arg);

    return this->GenerateToken();
}

}  // namespace igm::internal
