// Update CppShell.h to include the parser

#ifndef CPP_SHELL_H
#define CPP_SHELL_H

#include "ShellConfig.h"
#include "Parser.h"
#include <string>
#include <vector>
#include <deque>

class CppShell {
public:
    CppShell();
    ~CppShell();

    // Initialize the shell
    bool initialize();

    // Run the shell's main event loop
    int run();

    // Clean up resources
    void shutdown();

private:
    // Read a line of input from the user
    std::string readLine();

    // Display the shell prompt
    void displayPrompt();

    // Process a command line
    bool processCommand(const std::string& commandLine);

    // Parse and execute a command
    bool parseAndExecuteCommand(const std::string& commandLine);

    // Execute a parsed command
    bool executeCommand(const std::shared_ptr<Command>& command);

    // Add a command to history
    void addToHistory(const std::string& command);

    // Load command history from file
    bool loadHistory();

    // Save command history to file
    bool saveHistory();

    // Member variables
    std::string m_prompt;
    bool m_running;
    std::deque<std::string> m_history;
    std::string m_historyFile;
};

#endif // CPP_SHELL_H