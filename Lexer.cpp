// Lexer.cpp - Lexical analyzer implementation

#include "Lexer.h"
#include <cctype>

Lexer::Lexer(const std::string& input)
    : m_input(input), m_current(0) {}

Token Lexer::nextToken() {
    // Skip any whitespace
    skipWhitespace();

    // Check if we've reached the end of input
    if (isAtEnd()) {
        return Token(TokenType::END_OF_INPUT);
    }

    // Get the current character
    char c = peek();

    // Process the character based on what it is
    if (c == '|') {
        advance();
        if (peek() == '|') {
            advance();
            return Token(TokenType::OR_OPERATOR, "||");
        }
        return Token(TokenType::PIPE, "|");
    }
    else if (c == '&') {
        advance();
        if (peek() == '&') {
            advance();
            return Token(TokenType::AND_OPERATOR, "&&");
        }
        return Token(TokenType::BACKGROUND, "&");
    }
    else if (c == ';') {
        advance();
        return Token(TokenType::SEMICOLON, ";");
    }
    else if (c == '<') {
        advance();
        return Token(TokenType::REDIRECT_IN, "<");
    }
    else if (c == '>') {
        advance();
        if (peek() == '>') {
            advance();
            return Token(TokenType::REDIRECT_APPEND, ">>");
        }
        return Token(TokenType::REDIRECT_OUT, ">");
    }
    else if (c == '\n') {
        advance();
        return Token(TokenType::NEWLINE, "\n");
    }
    else if (c == '\"' || c == '\'') {
        return handleQuote(c);
    }
    else {
        // Default case: handle a word token
        return handleWord();
    }
}

std::vector<Token> Lexer::tokenize() {
    std::vector<Token> tokens;

    while (true) {
        Token token = nextToken();
        tokens.push_back(token);

        if (token.getType() == TokenType::END_OF_INPUT) {
            break;
        }
    }

    return tokens;
}

char Lexer::advance() {
    return m_input[m_current++];
}

char Lexer::peek() const {
    if (isAtEnd()) {
        return '\0';
    }
    return m_input[m_current];
}

char Lexer::peekNext() const {
    if (m_current + 1 >= m_input.size()) {
        return '\0';
    }
    return m_input[m_current + 1];
}

bool Lexer::match(char expected) {
    if (isAtEnd() || peek() != expected) {
        return false;
    }

    m_current++;
    return true;
}

Token Lexer::handleWord() {
    std::string value;

    // Keep consuming characters until we hit a delimiter
    while (!isAtEnd()) {
        char c = peek();

        // Break if we hit a special character or whitespace
        if (isspace(c) || c == '|' || c == '&' || c == ';' || c == '<' || c == '>') {
            break;
        }

        // Handle escaped characters
        if (c == '\\' && !isAtEnd()) {
            advance(); // Skip the backslash
            if (!isAtEnd()) {
                value += advance(); // Add the escaped character
            }
        }
        else {
            value += advance();
        }
    }

    return Token(TokenType::WORD, value);
}

Token Lexer::handleQuote(char quoteChar) {
    advance(); // Skip the opening quote
    std::string value;

    while (!isAtEnd() && peek() != quoteChar) {
        // Handle escaped characters within quotes
        if (peek() == '\\') {
            advance(); // Skip the backslash
            if (!isAtEnd()) {
                value += advance(); // Add the escaped character
            }
        }
        else {
            value += advance();
        }
    }

    if (!isAtEnd()) {
        advance(); // Skip the closing quote
    }

    return Token(TokenType::WORD, value);
}

void Lexer::skipWhitespace() {
    while (!isAtEnd()) {
        char c = peek();
        if (c == ' ' || c == '\t' || c == '\r') {
            advance();
        }
        else {
            break;
        }
    }
}