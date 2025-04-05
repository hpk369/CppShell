#pragma once
// Command.h - Command representation

#ifndef COMMAND_H
#define COMMAND_H

#include <string>
#include <vector>
#include <memory>
#include <unordered_map>

// Forward declarations
class Command;

// Redirection type
enum class RedirectType {
    INPUT,          // <
    OUTPUT,         // >
    APPEND          // >>
};

// Redirection structure
struct Redirection {
    RedirectType type;
    std::string target;

    Redirection(RedirectType t, const std::string& tgt)
        : type(t), target(tgt) {}
};

// Simple command (a single command with its arguments)
class SimpleCommand {
public:
    SimpleCommand(const std::string& name = "")
        : m_name(name) {}

    // Add an argument to the command
    void addArgument(const std::string& arg) {
        m_arguments.push_back(arg);
    }

    // Add a redirection
    void addRedirection(RedirectType type, const std::string& target) {
        m_redirections.emplace_back(type, target);
    }

    // Getters
    const std::string& getName() const { return m_name; }
    const std::vector<std::string>& getArguments() const { return m_arguments; }
    const std::vector<Redirection>& getRedirections() const { return m_redirections; }

    // Generate argv array for exec functions
    std::vector<const char*> getArgv() const;

    // Debugging
    std::string toString() const;

private:
    std::string m_name;
    std::vector<std::string> m_arguments;
    std::vector<Redirection> m_redirections;
};

// Command type enum
enum class CommandType {
    SIMPLE,         // A single command
    PIPELINE,       // Commands connected by pipes
    SEQUENCE,       // Commands separated by ;
    LOGICAL_AND,    // Commands separated by &&
    LOGICAL_OR      // Commands separated by ||
};

// Base Command class
class Command {
public:
    virtual ~Command() = default;

    // Get the type of this command
    virtual CommandType getType() const = 0;

    // Convert to string for debugging
    virtual std::string toString() const = 0;

    // Background execution flag
    bool isBackground() const { return m_background; }
    void setBackground(bool background) { m_background = background; }

private:
    bool m_background = false;
};

// Concrete command types
class SimpleCommandNode : public Command {
public:
    explicit SimpleCommandNode(SimpleCommand cmd)
        : m_command(std::move(cmd)) {}

    CommandType getType() const override { return CommandType::SIMPLE; }
    const SimpleCommand& getCommand() const { return m_command; }
    std::string toString() const override { return m_command.toString(); }

private:
    SimpleCommand m_command;
};

class PipelineNode : public Command {
public:
    PipelineNode(std::shared_ptr<Command> left, std::shared_ptr<Command> right)
        : m_left(std::move(left)), m_right(std::move(right)) {}

    CommandType getType() const override { return CommandType::PIPELINE; }
    const std::shared_ptr<Command>& getLeft() const { return m_left; }
    const std::shared_ptr<Command>& getRight() const { return m_right; }

    std::string toString() const override {
        return m_left->toString() + " | " + m_right->toString();
    }

private:
    std::shared_ptr<Command> m_left;
    std::shared_ptr<Command> m_right;
};

class SequenceNode : public Command {
public:
    SequenceNode(std::shared_ptr<Command> left, std::shared_ptr<Command> right)
        : m_left(std::move(left)), m_right(std::move(right)) {}

    CommandType getType() const override { return CommandType::SEQUENCE; }
    const std::shared_ptr<Command>& getLeft() const { return m_left; }
    const std::shared_ptr<Command>& getRight() const { return m_right; }

    std::string toString() const override {
        return m_left->toString() + "; " + m_right->toString();
    }

private:
    std::shared_ptr<Command> m_left;
    std::shared_ptr<Command> m_right;
};

class LogicalAndNode : public Command {
public:
    LogicalAndNode(std::shared_ptr<Command> left, std::shared_ptr<Command> right)
        : m_left(std::move(left)), m_right(std::move(right)) {}

    CommandType getType() const override { return CommandType::LOGICAL_AND; }
    const std::shared_ptr<Command>& getLeft() const { return m_left; }
    const std::shared_ptr<Command>& getRight() const { return m_right; }

    std::string toString() const override {
        return m_left->toString() + " && " + m_right->toString();
    }

private:
    std::shared_ptr<Command> m_left;
    std::shared_ptr<Command> m_right;
};

class LogicalOrNode : public Command {
public:
    LogicalOrNode(std::shared_ptr<Command> left, std::shared_ptr<Command> right)
        : m_left(std::move(left)), m_right(std::move(right)) {}

    CommandType getType() const override { return CommandType::LOGICAL_OR; }
    const std::shared_ptr<Command>& getLeft() const { return m_left; }
    const std::shared_ptr<Command>& getRight() const { return m_right; }

    std::string toString() const override {
        return m_left->toString() + " || " + m_right->toString();
    }

private:
    std::shared_ptr<Command> m_left;
    std::shared_ptr<Command> m_right;
};

#endif // COMMAND_H