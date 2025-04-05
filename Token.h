// Token.h - Token representation for lexical analysis

#ifndef TOKEN_H
#define TOKEN_H

#include <string>

// Token types for lexical analysis
enum class TokenType {
    WORD,           // Command or argument word
    PIPE,           // Pipe character '|'
    REDIRECT_IN,    // Input redirection '<'
    REDIRECT_OUT,   // Output redirection '>'
    REDIRECT_APPEND,// Append output redirection '>>'
    BACKGROUND,     // Background execution '&'
    SEMICOLON,      // Command separator ';'
    AND_OPERATOR,   // Logical AND '&&'
    OR_OPERATOR,    // Logical OR '||'
    NEWLINE,        // End of line
    END_OF_INPUT    // End of input stream
};

// Token class representing a lexical unit
class Token {
public:
    Token(TokenType type, const std::string& value = "")
        : m_type(type), m_value(value) {}

    // Getters
    TokenType getType() const { return m_type; }
    const std::string& getValue() const { return m_value; }

    // Helper methods for token type checking
    bool isWord() const { return m_type == TokenType::WORD; }
    bool isRedirect() const {
        return m_type == TokenType::REDIRECT_IN ||
            m_type == TokenType::REDIRECT_OUT ||
            m_type == TokenType::REDIRECT_APPEND;
    }
    bool isOperator() const {
        return m_type == TokenType::PIPE ||
            m_type == TokenType::SEMICOLON ||
            m_type == TokenType::AND_OPERATOR ||
            m_type == TokenType::OR_OPERATOR;
    }

    // Convert token to string representation (for debugging)
    std::string toString() const;

private:
    TokenType m_type;
    std::string m_value;
};

#endif // TOKEN_H