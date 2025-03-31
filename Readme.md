# CMakeLists.txt - Main build configuration

cmake_minimum_required(VERSION 3.10)
project(CppShell VERSION 0.1.0 LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Output directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# Add source files
set(SOURCES
    src/main.cpp
    src/CppShell.cpp
    # Additional source files will be added as components are implemented
)

# Add header files
set(HEADERS
    include/CppShell.h
    include/ShellConfig.h
    # Additional header files will be added as components are implemented
)

# Create executable
add_executable(cppshell ${SOURCES} ${HEADERS})

# Include directories
target_include_directories(cppshell PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# Find and link required system libraries
find_package(Threads REQUIRED)
target_link_libraries(cppshell PRIVATE Threads::Threads)

# Optional: Find and link readline for better input handling
find_package(Readline)
if(Readline_FOUND)
    target_compile_definitions(cppshell PRIVATE HAVE_READLINE)
    target_include_directories(cppshell PRIVATE ${Readline_INCLUDE_DIRS})
    target_link_libraries(cppshell PRIVATE ${Readline_LIBRARIES})
endif()

# Install target
install(TARGETS cppshell DESTINATION bin)

# Enable testing
enable_testing()

# Add test directory
add_subdirectory(tests)

# README.md - Project documentation

# CppShell

A modern C++ implementation of a command-line shell.

## Overview

CppShell is a feature-rich command-line interpreter written in C++17 that provides a user interface to access operating system services. This project demonstrates various aspects of systems programming, process management, and shell design.

## Features

- Command execution with arguments
- Input/output redirection (>, >>, <)
- Command piping (|)
- Environment variable support
- Job control (background processes, foreground/background toggling)
- Command history
- Tab completion (with readline support)
- Built-in commands (cd, echo, pwd, exit, etc.)
- Shell scripting support

## Project Structure

The project is divided into 10 logical components:

1. **Core Shell Framework** - Main event loop and user interaction
2. **Command Parsing** - Tokenizing and parsing user input
3. **Command Execution** - Executing commands and managing processes
4. **Built-in Commands** - Implementation of shell built-in commands
5. **Process Management** - Process creation, monitoring, and termination
6. **I/O Redirection** - Input/output redirection functionality
7. **Piping** - Command piping implementation
8. **Environment Variables** - Environment variable management
9. **Job Control** - Foreground/background job control
10. **Shell Scripting** - Support for shell scripts and control structures

## Building the Project

### Prerequisites

- C++17 compatible compiler (GCC 7+, Clang 5+, MSVC 2017+)
- CMake 3.10 or higher
- POSIX-compliant operating system (Linux, macOS, WSL)
- Optional: Readline library for enhanced input handling

### Build Instructions

```bash
# Clone the repository
git clone https://github.com/your-username/cppshell.git
cd cppshell

# Create build directory
mkdir build
cd build

# Configure and build
cmake ..
make

# Run the shell
./bin/cppshell
```

## Usage

Once CppShell is running, you can use it like any other command-line shell:

```
CppShell> ls -la
CppShell> echo Hello, World!
CppShell> cat file.txt | grep pattern > results.txt
```

Type `help` to see a list of available commands or `exit` to quit the shell.

## Development Roadmap

Each component will be implemented incrementally, with thorough documentation and testing at each stage. The project follows a modular design that allows for easy extension and modification.

## Contributing

Contributions are welcome! Please feel free to submit a Pull Request.

## License

This project is licensed under the MIT License - see the LICENSE file for details.

# .gitignore - Git ignore file

# Build directories
build/
bin/
lib/
obj/

# IDE files
.vscode/
.idea/
*.swp
*.swo

# Compiled files
*.o
*.obj
*.exe
*.out
*.app
*.dll
*.so
*.dylib

# CMake files
CMakeCache.txt
CMakeFiles/
cmake_install.cmake
Makefile
install_manifest.txt
compile_commands.json

# Dependency directories
external/

# User-specific files
*.user
*.suo
*.userprefs
.DS_Store

# History files
.cppshell_history
