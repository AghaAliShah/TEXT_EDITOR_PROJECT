#include "text_editor.h"
#include <windows.h>

using namespace std;

text_editor::text_editor() : current_line(0), full_content("") {
    lines.emplace_back("");
}

void text_editor::insert_char(char ch) {
    lines[current_line].insert_char(ch);
}

void text_editor::move_right() {
    if (lines[current_line].move_right()) {
        move_down();
    }
}

void text_editor::move_left() {
    if (lines[current_line].move_left()) {
        if (current_line > 0) {
            current_line--;
            lines[current_line].cursor_at_end();
        }
    }
}

void text_editor::move_up() {
    if (current_line > 0) {
        current_line--;
        lines[current_line].move_cursor_at_zero_position();
    }
}

void text_editor::move_down() {
    if (current_line < lines.size() - 1) {
        current_line++;
        lines[current_line].move_cursor_at_zero_position();
    }
}

void text_editor::new_line() {
    if (current_line <= -1) {
        lines.emplace_back();
        current_line = 0;
    }
    else {
        line new_line;
        node* cursor = lines[current_line].get_cursor();
        if (cursor == nullptr) {
            cursor = lines[current_line].get_head();
            if (cursor != nullptr) {
                new_line.insert_char(cursor->letter);
            }
        }

        while (cursor && cursor->next) {
            cursor = cursor->next;
            new_line.insert_char(cursor->letter);
        }

        lines[current_line].delete_after_cursor();
        lines.insert(lines.begin() + current_line + 1, new_line);
        current_line++;
    }
    lines[current_line].move_cursor_at_zero_position();
}

void text_editor::yank_line() {
    lines[current_line].yank(copy_buffer);
    if (!copy_buffer.empty()) {
        cd.setStatus("successful");
    }
}

void text_editor::yank_multiple(int num) {
    copy_buffer.clear();
    for (int i = 0; i < num; i++) {
        lines[current_line].yank_m(copy_buffer);
        copy_buffer += '\n';
        move_down();
    }
    for (int i = 0; i < num; i++) {
        move_up();
    }
    cd.setStatus("successful");
}

void text_editor::paste_after() {
    line new_line;
    new_line.paste_after(copy_buffer);
    lines.insert(lines.begin() + current_line + 1, new_line);
    cd.setStatus("successful");

}

void text_editor::back_space() {
    if (lines[current_line].get_cursor()) {
        lines[current_line].del_at_cursor();
        cd.setStatus("successful");

    }
    else if (!lines[current_line].get_cursor() && current_line > 0) {
        current_line--;
        lines[current_line].cursor_at_end();
        lines[current_line].del_at_cursor();
        cd.setStatus("successful");

    }
    else {
        cout << "no element left" << endl;
        cd.setStatus("unsuccessful");
        return;
    }
    cd.setStatus("successful");
}

void text_editor::paste_before() {
    line new_line;
    new_line.paste_after(copy_buffer);
    lines.insert(lines.begin() + current_line - 1, new_line);
    cd.setStatus("successful");

}

void text_editor::enter_insert_mode() {
    insert_mode = true;

}

void text_editor::exit_insert_mode() {
    insert_mode = false;
}

bool text_editor::is_insert_mode() const {
    return insert_mode;
}

void text_editor::delete_current_line() {
    if (current_line <= -1) {
        cd.setStatus("unsuccessful");

        return;
    }
    if (current_line == 0) {
        lines.erase(lines.begin() + current_line);
        current_line++;
        lines[current_line].cursor_at_end();
    }
    else if (lines.size() == 1) {
        move_to_start_of_line();
        insert_char(' ');
        move_right();
        delete_to_end_of_line();
    }
    else {
        lines.erase(lines.begin() + current_line);
        current_line--;
        lines[current_line].cursor_at_end();
    }
    cd.setStatus("successful");
}

void text_editor::delete_nth_line(int num) {
    num--;
    if (num < 0 || num >= lines.size()) {
        cerr << "out of bounds: num = " << num << ", size = " << lines.size() << endl;
        cd.setStatus("unsuccessful");

        return;
    }
    else {
        current_line = num;
        delete_current_line();
    }
    cd.setStatus("successful");
}

void text_editor::delete_to_end_of_line() {
    lines[current_line].delete_after_cursor();
    cd.setStatus("successful");

}

void text_editor::delete_character_at_cursor() {
    node* cursor = lines[current_line].get_cursor();
    if (cursor == nullptr) {
        lines[current_line - 1].cursor_at_end();
        cursor = lines[current_line].get_head();
        lines[current_line - 1].insert_char(cursor->letter);
        while (cursor && cursor->next) {
            cursor = cursor->next;
            lines[current_line - 1].insert_char(cursor->letter);
        }
        delete_current_line();
        cd.setStatus("successful");
        return;
    }
    else if (lines[current_line].get_head() == nullptr) {
        delete_current_line();
    }
    else {
        lines[current_line].del_at_cursor();
    }
    cd.setStatus("successful");
}

void text_editor::move_to_start_of_line() {
    lines[current_line].move_cursor_at_zero_position();
    cd.setStatus("successful");
}


void  text_editor::move_to_end_of_line() {
    lines[current_line].cursor_at_end();
    cd.setStatus("successful");

}
void  text_editor::moveToNextWord() {
    if (current_line < lines.size()) {
        if (!lines[current_line].if_tail()) {
            lines[current_line].move_to_nex_word();
        }
        if (lines[current_line].if_tail()) {
            current_line++;
            lines[current_line].move_cursor_at_zero_position();
            lines[current_line].move_to_nex_word();
        }
        cd.setStatus("successful");

    }
}

void text_editor::moveToPreviousWord() {
    if (current_line >= 0) {
        if (!lines[current_line].if_head()) {
            lines[current_line].move_to_pre_word();
        }
        if (lines[current_line].if_head()) {
            current_line--;
            lines[current_line].cursor_at_end();
            lines[current_line].move_to_pre_word();
        }
        cd.setStatus("successful");

    }
}

void  text_editor::moveToWordEnd() {
    lines[current_line].word_end();
    cd.setStatus("successful");

}

void  text_editor::display() {
    system("cls");
    cout << "-----------------\n";
    for (int i = 0; i < lines.size(); i++) {
        lines[i].display(i == current_line);
        cout << endl;
    }
    cout << "-----------------\n";
    cout << (insert_mode ? "-- INSERT MODE --" : "-- NORMAL MODE --") << endl;
}

void  text_editor::updateDisplay() {
    for (int i = 0; i < lines.size(); i++) {

        cout << (i + 1) << "|";
        lines[i].display(i == current_line);
        cout << endl;
    }
    cout << "|";
    cout << endl;

    cout << "Current line |" << current_line + 1 << endl;
    cout << "---------------------------" << endl;
    updateStatusLine();
}

void  text_editor::updateStatusLine() {
    cout << getStatusLineText() << endl;
}

string  text_editor::getStatusLineText() {
    string mode = insert_mode ? "INSERT MODE" : "VISUAL MODE";
    string modify = file_manager.hasUnsavedChanges() ? "  " : " [+] ";

    return mode + " | Line: " + to_string(current_line + 1) +
        ", Col: " + to_string(lines[current_line].cursor_p()) +
        " | Total Lines: " + to_string(lines.size()) + modify + "| status of current executed command: " + cd.get_status();
}
void  text_editor::set_full_content() {
    full_content.clear();
    for (int i = 0; i < lines.size(); i++) {
        full_content += lines[i].get_content() + '\n';

    }
}
void  text_editor::insert_lines(string s) {
    for (char i : s) {
        insert_char(i);
    }
}
bool  text_editor::handleFileCommand(const string& cmd) {
    if (cmd == "save") {
        cout << "enter file to save: ";
        string file_name;
        cin >> file_name;
        set_full_content();
        file_manager.set_content(full_content);
        if (file_manager.saveFile(file_name)) {
            cout << "file: " << file_manager.getCurrentFileName() << " has been successfully saved plz wait" << endl;
            updateModifiedStatus();
            cd.setStatus("successful");

            Sleep(5000);

            return true;
        }
        else {
            cout << "file: " << file_manager.getCurrentFileName() << " unable to save" << endl;
            cd.setStatus("unsuccessful");

            Sleep(5000);
            return false;

        }

    }

    if (cmd == "load") {
        cout << "enter file to load: ";
        string file_name;
        cin >> file_name;
        if (file_manager.loadFile(file_name)) {
            full_content = file_manager.get_content();
            insert_lines(full_content);
            cout << "file: " << file_manager.getCurrentFileName() << " has been successfully loaded" << endl;
            cd.setStatus("successful");
            return true;


        }
        else {
            cout << "file: " << file_manager.getCurrentFileName() << " unable to load" << endl;
            cd.setStatus("unsuccessful");
            Sleep(5000);
            return false;
        }

    }
    return false;
}
void  text_editor::updateModifiedStatus() {
    file_manager.markAsModified();
}
void  text_editor::set_cmd(char c) {
    if (c == 's') {
        handleFileCommand("save");
    }
    if (c == 'l') {
        handleFileCommand("load");
    }
    if (c == 'c') {
        cout << "command: ";
        string cm;
        cin >> cm;
        cout << endl;
        cout << "no. of times: ";
        int n;
        cin >> n;
        execute_with_count(n, cm);

    }
    if (c == '|') {
        int n;
        cout << "enter line to be deleted: ";
        cin >> n;
        delete_nth_line(n);
        execute_command("delete " + to_string(n) + "th line");
    }
    if (c == '/') {
        string p;
        cout << "enter pattern: ";
        cin >> p;
        search(p);
    }
    if (c == ':') {
        string o;
        cout << "enter old pattern to be changed: ";
        cin >> o;
        string n;
        cout << "enter new pattern to be added: ";
        cin >> n;
        bool g;
        cout << "over all occurrences (y/n): ";
        char a;
        cin >> a;
        if (a == 'y') { g = true; }
        else {
            g = false;
        }
        replace(o, n, g);
    }
}

void  text_editor::indent(bool r) {
    if (r) {
        lines[current_line].indent_r(true);
        cd.setStatus("successful");

    }
    else {
        lines[current_line].indent_r(false);
        cd.setStatus("successful");

    }
}
void  text_editor::join_lines() {
    if (lines.size() >= 1 && current_line < lines.size() - 1) {
        lines[current_line + 1].yank(copy_buffer);
        delete_nth_line(current_line + 2);
        lines[current_line].join(copy_buffer);
        cd.setStatus("successful");

    }
    else {
        cerr << "single cant join" << endl;
        cd.setStatus("unsuccessful");
    }
}
void text_editor::execute_with_count(int count, const string& cmd) {
    if (cmd == "d") {
        for (int i = 0; i < count; i++) {
            delete_current_line();

        }
        execute_command("delete lines " + to_string(count) + "times");

    }
    if (cmd == "y") {
        yank_multiple(count);
        execute_command("yank lines " + to_string(count) + "times");

    }
    if (cmd == "j") {
        for (int i = 0; i < count; i++) {
            join_lines();
        }
        execute_command("join lines " + to_string(count) + "times");
    }
}
void  text_editor::execute_command(string i) {
    cd.addToHistory(i);
}
void  text_editor::get_history() {
    
    cd.print_history();
    Sleep(5000);
}
void  text_editor::get_prev_cmd() {
    cout << cd.getPreviousCommand() << endl;
}
void  text_editor::get_nex_cmd() {
    cout << cd.getNextCommand() << endl;
}
void  text_editor::print_search() {

    cout << "pattern: " << last_pattern << endl;
    cout << "location: " << endl;
    cout << "line no: " << last_match_line << endl;
    cout << "col no: " << last_match_col << endl;

}
bool  text_editor::search(const string& pattern) {
    last_pattern = pattern;
    cout << "searching for pattern: " << pattern << endl;

    for (size_t i = 0; i < lines.size(); ++i) {
        cout << "checking line " << i + 1 << ": " << lines[i].get_content() << endl;
        Sleep(5000);
        size_t pos = lines[i].get_content().find(pattern);

        if (pos != string::npos) {
            last_match_line = i;
            last_match_col = pos;
            cd.setStatus("successful");
            print_search();
            Sleep(8000);

            return true;
        }
    }

    cd.setStatus("unsuccessful");
    cout << "Pattern not found." << endl;
    Sleep(5000);
    return false;
}
bool  text_editor::find_prev() {
    cout << "searching for pattern: " << last_pattern << endl;
    for (size_t i = last_match_line; i > 0; --i) {
        cout << "checking line " << i + 1 << ": " << lines[i].get_content() << endl;
        Sleep(5000);
        size_t pos;
        if (i == last_match_line) {
            pos = lines[i].get_content_pre(last_match_col).find(last_pattern);
        }
        else {
            pos = lines[i].get_content().find(last_pattern);
        }
        if (pos != string::npos) {
            last_match_line = i;
            last_match_col = pos;
            cd.setStatus("successful");
            print_search();
            Sleep(8000);
            return true;
        }
    }
    cd.setStatus("unsuccessful");
    cout << "Pattern not found." << endl;
    Sleep(5000);
    return false;
}
bool  text_editor::find_next() {
    cout << "searching for pattern: " << last_pattern << endl;
    for (size_t i = last_match_line; i < lines.size(); ++i) {
        cout << "checking line " << i + 1 << ": " << lines[i].get_content() << endl;
        Sleep(5000);
        size_t pos;
        if (i == last_match_line) {
            pos = lines[i].get_content_next(last_match_col).find(last_pattern);
        }
        else {
            pos = lines[i].get_content().find(last_pattern);
        }
        if (pos != string::npos) {
            last_match_line = i;
            last_match_col = pos;
            cd.setStatus("successful");
            print_search();
            Sleep(8000);
            return true;
        }
    }
    cd.setStatus("unsuccessful");
    cout << "Pattern not found." << endl;
    Sleep(5000);
    return false;
}

bool  text_editor::replace(const string& old, const string& newStr, bool global = false) {
    cout << "searching for pattern: " << old << endl;
    if (!global) {
        for (size_t i = 0; i < lines.size(); ++i) {
            size_t pos = lines[i].get_content().find(old);
            if (pos != string::npos) {
                cd.setStatus("successful");
                string s = lines[i].get_content();
                s.replace(pos, old.size(), newStr);
                lines[i].set_content(s);
                lines[i].move_cursor_at_zero_position();
                lines[i].delete_after_cursor();
                lines[i].paste_after(s);
                return true;
            }
        }
    }
    else {
        bool foundAny = false;
        for (size_t i = 0; i < lines.size(); ++i) {
            string content = lines[i].get_content();
            size_t pos = content.find(old);

            while (pos != string::npos) {
                cd.setStatus("successful");
                content.replace(pos, old.size(), newStr);
                pos = content.find(old, pos + newStr.size());

                lines[i].set_content(content);
                lines[i].move_cursor_at_zero_position();
                lines[i].delete_after_cursor();
                lines[i].paste_after(content);
                foundAny = true;
            }
        }

        if (!foundAny) {
            cd.setStatus("unsuccessful");
            cout << "Pattern not found." << endl;
            Sleep(5000);
            return false;
        }
    }

    return true;
}

