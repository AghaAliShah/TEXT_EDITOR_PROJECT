#pragma once

#include <vector>
#include <string>
#include <iostream>

using namespace std;

class CommandMode {
private:
    vector<string> commandHistory;
    size_t historyIndex;
    string statusMessage;

public:
    CommandMode();
    void addToHistory(const string& cmd);
    string getPreviousCommand();
    string getNextCommand();
    void setStatus(const string& msg);
    string get_status();
    void print_history();
};
