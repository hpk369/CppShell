// CppShell.cpp - Main shell class implementation

#include "CppShell.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <signal.h>

// #include <filesystem> -- below is the replacement of this library
#ifdef _WIN32
#include <direct.h>
#define getcwd _getcwd
#else
#include <unistd.h>
#endif


// Static instance for signal handling
static CppShell* g_shellInstance = nullptr;

// Signal handler
void signalHandler(int sig) {
    if (g_shellInstance != nullptr) {
        if (sig == SIGINT) {
            std::cout << "\n" << config::DEFAULT_PROMPT;
            std::cout.flush();
        }
    }
}

CppShell::CppShell() :
    m_prompt(config::DEFAULT_PROMPT),
    m_running(false) {

    // Set up history file path
    const char* homeDir = getenv("USERPROFILE");
    if (homeDir != nullptr) {
        m_historyFile = std::string(homeDir) + "/" + config::HISTORY_FILE;
    }
    else {
        m_historyFile = config::HISTORY_FILE;
    }

    // Set global instance for signal handling
    g_shellInstance = this;
}

CppShell::~CppShell() {
    g_shellInstance = nullptr;
}

bool CppShell::initialize() {
    // Set up signal handlers
    signal(SIGINT, signalHandler);  // Handle Ctrl+C

    // Load command history
    loadHistory();

    // Display welcome message
    std::cout << config::SHELL_NAME << " v" << config::VERSION << std::endl;
    std::cout << "Type 'help' for a list of commands or 'exit' to quit." << std::endl;

    return true;
}

int CppShell::run() {
    m_running = true;

    while (m_running) {
        // Display prompt
        displayPrompt();

        // Read user input
        std::string commandLine = readLine();

        // Skip empty lines
        if (commandLine.empty()) {
            continue;
        }

        // Add to history
        addToHistory(commandLine);

        // Process the command
        if (!processCommand(commandLine)) {
            // Handle command errors
        }
    }

    return 0;
}

void CppShell::shutdown() {
    // Save command history
    saveHistory();

    std::cout << "Goodbye!" << std::endl;
}

std::string CppShell::readLine() {
    std::string line;
    std::getline(std::cin, line);

    // Check for EOF (Ctrl+D)
    if (std::cin.eof()) {
        m_running = false;
        std::cout << std::endl;
        return "exit";
    }

    return line;
}

void CppShell::displayPrompt() {
    std::cout << m_prompt;
    std::cout.flush();
}

bool CppShell::processCommand(const std::string& commandLine) {
    // This is a placeholder implementation that will be expanded
    // in the Command Parsing and Execution components

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
    else {
        // For now, just echo the command
        std::cout << "Command not implemented: " << commandLine << std::endl;
        return true;
    }
}

void CppShell::addToHistory(const std::string& command) {
    // Don't add empty commands or duplicates of the last command
    if (command.empty() || (!m_history.empty() && m_history.back() == command)) {
        return;
    }

    m_history.push_back(command);

    // Limit history size
    if (m_history.size() > config::MAX_HISTORY_SIZE) {
        m_history.pop_front();
    }
}

bool CppShell::loadHistory() {
    std::ifstream historyFile(m_historyFile);
    if (!historyFile.is_open()) {
        return false;
    }

    std::string line;
    while (std::getline(historyFile, line)) {
        if (!line.empty()) {
            m_history.push_back(line);
        }
    }

    // Limit history size
    while (m_history.size() > config::MAX_HISTORY_SIZE) {
        m_history.pop_front();
    }

    return true;
}

bool CppShell::saveHistory() {
    std::ofstream historyFile(m_historyFile);
    if (!historyFile.is_open()) {
        std::cerr << "Warning: Could not save command history." << std::endl;
        return false;
    }

    for (const auto& cmd : m_history) {
        historyFile << cmd << std::endl;
    }

    return true;
}