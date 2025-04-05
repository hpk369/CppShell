// Update CppShell.cpp to use the parser

#include "CppShell.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <filesystem>
#include <signal.h>

// ... (existing code)

bool CppShell::processCommand(const std::string& commandLine) {
    try {
        return parseAndExecuteCommand(commandLine);
    }
    catch (const ParseError& e) {
        std::cerr << e.what() << std::endl;
        return false;
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return false;
    }
}

bool CppShell::parseAndExecuteCommand(const std::string& commandLine) {
    // Basic built-in commands for now
    if (commandLine == "exit" || commandLine == "quit") {
        m_running = false;
        return true;
    }
    else if (commandLine == "help") {
        std::cout << "Available commands:" << std::endl;
        std::cout << "  help - Display this help message" << std::endl;
        std::cout << "  exit - Exit the shell" << std::endl;
        return true;
    }

    // Parse the command
    Parser parser(commandLine);
    std::shared_ptr<Command> command;

    try {
        command = parser.parse();
    }
    catch (const ParseError& e) {
        std::cerr << e.what() << std::endl;
        return false;
    }

    // Print the parsed command (for debugging)
    std::cout << "Parsed command: " << command->toString() << std::endl;

    // In Component 2, we just parse the command but don't execute it yet
    // This will be implemented in Component 3
    std::cout << "Command execution not implemented yet." << std::endl;
    return true;
}

bool CppShell::executeCommand(const std::shared_ptr<Command>& command) {
    // This will be implemented in Component 3
    return true;
}