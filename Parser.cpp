// Parser.cpp - Command parser implementation

#include "Parser.h"

Parser::Parser(const std::string& input)
    : m_lexer(input), m_current(0) {
    // Tokenize the entire input
    m_tokens = m_lexer.tokenize();
}

std::shared_ptr<Command> Parser::parse() {
    // Start parsing from the top-level rule
    auto command = parseCommand();

    // Check if we reached the end of input
    if (m_current < m_tokens.size() &&
        m_tokens[m_current].getType() != TokenType::END_OF_INPUT) {
        throw ParseError("Unexpected tokens at end of input");
    }

    return command;
}

std::shared_ptr<Command> Parser::parseCommand() {
    // Parse a command (sequence of commands separated by semicolons)
    auto command = parseLogicalOr();

    while (match(TokenType::SEMICOLON)) {
        auto right = parseLogicalOr();
        command = std::make_shared<SequenceNode>(command, right);
    }

    // Check for background execution
    if (match(TokenType::BACKGROUND)) {
        command->setBackground(true);
    }

    return command;
}

std::shared_ptr<Command> Parser::parseLogicalOr() {
    // Parse logical OR expressions (commands separated by ||)
    auto command = parseLogicalAnd();

    while (match(TokenType::OR_OPERATOR)) {
        auto right = parseLogicalAnd();
        command = std::make_shared<LogicalOrNode>(command, right);
    }

    return command;
}

std::shared_ptr<Command> Parser::parseLogicalAnd() {
    // Parse logical AND expressions (commands separated by &&)
    auto command = parsePipeline();

    while (match(TokenType::AND_OPERATOR)) {
        auto right = parsePipeline();
        command = std::make_shared<LogicalAndNode>(command, right);
    }

    return command;
}

std::shared_ptr<Command> Parser::parsePipeline() {
    // Parse a pipeline (commands separated by pipes)
    auto command = parseSimpleCommand();

    while (match(TokenType::PIPE)) {
        auto right = parseSimpleCommand();
        command = std::make_shared<PipelineNode>(command, right);
    }

    return command;
}

std::shared_ptr<Command> Parser::parseSimpleCommand() {
    // Parse a simple command (command name + args + redirections)
    if (!check(TokenType::WORD)) {
        throw ParseError("Expected a command");
    }

    Token nameToken = advance();
    SimpleCommand cmd(nameToken.getValue());

    // Parse arguments and redirections
    while (check(TokenType::WORD) || check(TokenType::REDIRECT_IN) ||
        check(TokenType::REDIRECT_OUT) || check(TokenType::REDIRECT_APPEND)) {

        if (check(TokenType::WORD)) {
            cmd.addArgument(advance().getValue());
        }
        else {
            parseRedirections(cmd);
        }
    }

    return std::make_shared<SimpleCommandNode>(cmd);
}

void Parser::parseRedirections(SimpleCommand& cmd) {
    // Handle redirections
    if (match(TokenType::REDIRECT_IN)) {
        // Input redirection
        expect(TokenType::WORD, "Expected filename after <");
        cmd.addRedirection(RedirectType::INPUT, advance().getValue());
    }
    else if (match(TokenType::REDIRECT_OUT)) {
        // Output redirection
        expect(TokenType::WORD, "Expected filename after >");
        cmd.addRedirection(RedirectType::OUTPUT, advance().getValue());
    }
    else if (match(TokenType::REDIRECT_APPEND)) {
        // Append redirection
        expect(TokenType::WORD, "Expected filename after >>");
        cmd.addRedirection(RedirectType::APPEND, advance().getValue());
    }
}

Token Parser::peek() const {
    if (m_current >= m_tokens.size()) {
        return Token(TokenType::END_OF_INPUT);
    }
    return m_tokens[m_current];
}

Token Parser::advance() {
    if (!isAtEnd()) {
        m_current++;
    }
    return m_tokens[m_current - 1];
}

bool Parser::check(TokenType type) const {
    if (isAtEnd()) {
        return false;
    }
    return peek().getType() == type;
}

bool Parser::match(TokenType type) {
    if (check(type)) {
        advance();
        return true;
    }
    return false;
}

void Parser::expect(TokenType type, const std::string& message) {
    if (check(type)) {
        return;
    }
    throw ParseError(message);
}

bool Parser::isAtEnd() const {
    return m_current >= m_tokens.size() ||
        m_tokens[m_current].getType() == TokenType::END_OF_INPUT;