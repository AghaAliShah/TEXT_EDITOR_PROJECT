#include "command_mode.h"

using namespace std;

CommandMode::CommandMode() : historyIndex(0) {}

void CommandMode::addToHistory(const string& cmd) {
    if (!cmd.empty()) {
        commandHistory.push_back(cmd);
        historyIndex = commandHistory.size();
    }
}

string CommandMode::getPreviousCommand() {
    if (commandHistory.empty()) {
        return "no command to show";
    }
    if (historyIndex > 0) {
        historyIndex--;
    }
    return commandHistory[historyIndex];
}

string CommandMode::getNextCommand() {
    if (commandHistory.empty()) {
        return "no command to show";
    }
    if (historyIndex < commandHistory.size() - 1) {
        historyIndex++;
    }
    return commandHistory[historyIndex];
}

void CommandMode::setStatus(const string& msg) {
    statusMessage = msg;
}

string CommandMode::get_status() {
    return statusMessage;
}

void CommandMode::print_history() {
    if (commandHistory.empty()) {
        cout << "no command to show" << endl;
        return;
    }
    int id = 0;
    for (const auto& cmd : commandHistory) {
        cout << id << ": " << cmd << endl;
        id++;
    }
}
