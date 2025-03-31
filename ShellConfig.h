// ShellConfig.h - Configuration parameters for the shell

#ifndef SHELL_CONFIG_H
#define SHELL_CONFIG_H

#include <string>
#include <vector>

namespace config {
    // Shell information
    const std::string SHELL_NAME = "CppShell";
    const std::string VERSION = "0.1.0";

    // Default prompt
    const std::string DEFAULT_PROMPT = "CppShell> ";

    // History settings
    const unsigned int MAX_HISTORY_SIZE = 1000;
    const std::string HISTORY_FILE = ".cppshell_history";

    // Environment
    const std::vector<std::string> DEFAULT_PATH = {
        "/usr/local/bin",
        "/usr/bin",
        "/bin"
    };
}

#endif // SHELL_CONFIG_H