#pragma once

#include <iostream>
#include <vector>
#include <string>
#include "line.h"
#include "file_manager.h"
#include "command_mode.h"

using namespace std;

enum Mode { INSERT, NORMAL };

struct EditorStatus {
    Mode currentMode;           // INSERT or NORMAL
    size_t cursorLine;          // Current line number
    size_t cursorColumn;        // Current column number
    size_t totalLines;          // Total lines in document
    string lastCommand;    // Last executed command
};


class text_editor {
private:
    vector<line> lines;
    int current_line;
    bool insert_mode;
    string copy_buffer;
    EditorStatus status;
    FileManager file_manager;
    CommandMode cd;

    // search engine
    string last_pattern;
    size_t last_match_line;
    size_t last_match_col;
    string full_content;

public:
    text_editor();

    void insert_char(char ch);
    void move_right();
    void move_left();
    void move_up();
    void move_down();
    void new_line();
    void yank_line();
    void yank_multiple(int num);
    void paste_after();
    void back_space();
    void paste_before();

    void enter_insert_mode();
    void exit_insert_mode();
    bool is_insert_mode() const;

    void delete_current_line();
    void delete_nth_line(int num);
    void delete_to_end_of_line();
    void delete_character_at_cursor();

    void move_to_start_of_line();
    void move_to_end_of_line();
    void moveToNextWord();
    void moveToPreviousWord();
    void moveToWordEnd();

    void display();
    void updateDisplay();
    void updateStatusLine();
    string getStatusLineText();

    void set_full_content();
    void insert_lines(string s);

    bool handleFileCommand(const string& cmd);
    void updateModifiedStatus();
    void set_cmd(char c);
    void indent(bool r);
    void join_lines();
    void execute_with_count(int count, const string& cmd);
    void execute_command(string i);
    void get_history();
    void get_prev_cmd();
    void get_nex_cmd();
    void print_search();
    bool find_prev();
    bool find_next();
    bool search(const string& pattern);
    bool replace(const string& old_pattern, const string& new_pattern, bool global);
};