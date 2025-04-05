// Command.cpp - Command implementation

#include "Command.h"
#include <sstream>

std::vector<const char*> SimpleCommand::getArgv() const {
    std::vector<const char*> argv;

    // Add the command name as the first argument
    argv.push_back(m_name.c_str());

    // Add the rest of the arguments
    for (const auto& arg : m_arguments) {
        argv.push_back(arg.c_str());
    }

    // Add a nullptr at the end (required by exec functions)
    argv.push_back(nullptr);

    return argv;
}

std::string SimpleCommand::toString() const {
    std::ostringstream oss;
    oss << m_name;

    for (const auto& arg : m_arguments) {
        oss << " " << arg;
    }

    for (const auto& redir : m_redirections) {
        switch (redir.type) {
        case RedirectType::INPUT:
            oss << " < " << redir.target;
            break;
        case RedirectType::OUTPUT:
            oss << " > " << redir.target;
            break;
        case RedirectType::APPEND:
            oss << " >> " << redir.target;
            break;
        }
    }

    return oss.str();
}