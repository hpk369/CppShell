// main.cpp - Entry point for CppShell

#include "CppShell.h"
#include <iostream>

int main(int argc, char* argv[]) {
    try {
        // Create shell instance
        CppShell shell;

        // Initialize the shell
        if (!shell.initialize()) {
            std::cerr << "Failed to initialize shell. Exiting." << std::endl;
            return 1;
        }

        // Run the shell's main loop
        int exitCode = shell.run();

        // Perform cleanup
        shell.shutdown();

        return exitCode;
    }
    catch (const std::exception& e) {
        std::cerr << "Fatal error: " << e.what() << std::endl;
        return 1;
    }
}