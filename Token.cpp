// Token.cpp - Token implementation

#include "Token.h"

std::string Token::toString() const {
    std::string typeStr;

    switch (m_type) {
    case TokenType::WORD: typeStr = "WORD"; break;
    case TokenType::PIPE: typeStr = "PIPE"; break;
    case TokenType::REDIRECT_IN: typeStr = "REDIRECT_IN"; break;
    case TokenType::REDIRECT_OUT: typeStr = "REDIRECT_OUT"; break;
    case TokenType::REDIRECT_APPEND: typeStr = "REDIRECT_APPEND"; break;
    case TokenType::BACKGROUND: typeStr = "BACKGROUND"; break;
    case TokenType::SEMICOLON: typeStr = "SEMICOLON"; break;
    case TokenType::AND_OPERATOR: typeStr = "AND_OPERATOR"; break;
    case TokenType::OR_OPERATOR: typeStr = "OR_OPERATOR"; break;
    case TokenType::NEWLINE: typeStr = "NEWLINE"; break;
    case TokenType::END_OF_INPUT: typeStr = "END_OF_INPUT"; break;
    default: typeStr = "UNKNOWN"; break;
    }

    return "Token{type=" + typeStr + ", value='" + m_value + "'}";
}
