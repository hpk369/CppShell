// Parser.h - Command parser

#ifndef PARSER_H
#define PARSER_H

#include "Lexer.h"
#include "Command.h"
#include <memory>
#include <vector>
#include <stdexcept>

// Exception for parsing errors
class ParseError : public std::runtime_error {
public:
    explicit ParseError(const std::string& message)
        : std::runtime_error("Parse error: " + message) {}
};

class Parser {
public:
    explicit Parser(const std::string& input);

    // Parse the input into a command structure
    std::shared_ptr<Command> parse();

private:
    // Recursive descent parsing methods
    std::shared_ptr<Command> parseCommand();
    std::shared_ptr<Command> parseLogicalOr();
    std::shared_ptr<Command> parseLogicalAnd();
    std::shared_ptr<Command> parsePipeline();
    std::shared_ptr<Command> parseSimpleCommand();

    // Helper methods
    Token peek() const;
    Token advance();
    bool check(TokenType type) const;
    bool match(TokenType type);
    void expect(TokenType type, const std::string& message);

    // Handle redirections
    void parseRedirections(SimpleCommand& cmd);

    // Member variables
    Lexer m_lexer;
    std::vector<Token> m_tokens;
    size_t m_current;
};

#endif // PARSER_H

