// Lexer.h - Lexical analyzer for breaking input into tokens

#ifndef LEXER_H
#define LEXER_H

#include "Token.h"
#include <string>
#include <vector>
#include <memory>

class Lexer {
public:
    // Constructor takes input string to tokenize
    explicit Lexer(const std::string& input);

    // Get the next token from the input
    Token nextToken();

    // Tokenize the entire input at once
    std::vector<Token> tokenize();

    // Check if the lexer has reached the end of input
    bool isAtEnd() const { return m_current >= m_input.size(); }

private:
    // Helper methods for tokenization
    char advance(); // Move to next character and return it
    char peek() const; // Look at current character without advancing
    char peekNext() const; // Look ahead one character
    bool match(char expected); // Check if current char matches expected and advance if so

    // Token generation methods
    Token handleWord(); // Process a word token (command or argument)
    Token handleQuote(char quoteChar); // Process a quoted string
    Token handleOperator(); // Process an operator or redirect

    // Skip whitespace characters
    void skipWhitespace();

    // Member variables
    std::string m_input; // Input string
    size_t m_current; // Current position in input
};

#endif // LEXER_H