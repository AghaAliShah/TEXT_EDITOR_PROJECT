#include"text_editor.h"
#include <cstdlib>
#include <conio.h>
using namespace std;

int get_char() {
    int ch = _getch();
    if (ch == 0 || ch == 224) {
        ch = _getch();
        switch (ch) {
        case 72: return 65;
        case 80: return 66;
        case 77: return 67;
        case 75: return 68;
        }
    }
    return ch;
}

int main() {
    text_editor editor;
    int cmd;

    while (true) {
        editor.display();
        editor.updateDisplay();
        cmd = get_char();

        if (cmd == 27) {
            editor.exit_insert_mode();
            continue;
        }

        if (editor.is_insert_mode()) {
            switch (cmd) {
            case 65: editor.move_up();
                break;
            case 66: editor.move_down();
                break;
            case 67: editor.move_right();
                break;
            case 68: editor.move_left();
                break;
            case '\r': editor.new_line();
                break;
            case'\b':editor.back_space();
                break;
            default: editor.insert_char(cmd);
                break;
            }
        }
        else {
            switch (cmd) {

            case 'i':
                editor.enter_insert_mode();

                break;
            case 'I':
                editor.enter_insert_mode();
                break;
            case 'q':
                return 0;
            case 65: editor.move_up();
                break;
            case 66: editor.move_down();
                break;
            case 67: editor.move_right();
                break;
            case 68: editor.move_left();
                break;
            case 8: editor.delete_character_at_cursor();
                editor.execute_command("delete character at cursor");
                break;
            case 127: editor.delete_character_at_cursor();
                editor.execute_command("delete character at cursor");

                break;
            case 'd': editor.delete_current_line();
                editor.execute_command("delete current line");

                break;
            case 'y': editor.yank_line();
                editor.execute_command("yank character at cursor");

                break;
            case 'p': editor.paste_after();
                editor.execute_command("paste after current line");

                break;
            case 'P': editor.paste_before();
                editor.execute_command("paste before current line");

                break;
            case '0': editor.move_to_start_of_line();
                editor.execute_command("move to start of current line");

                break;
            case '$': editor.move_to_end_of_line();
                editor.execute_command("move to end of current line");

                break;
            case 'w':editor.moveToNextWord();
                editor.execute_command("move to next word");

                break;
            case'b':editor.moveToPreviousWord();
                editor.execute_command("move to previous word");

                break;
            case 'e':editor.moveToWordEnd();
                editor.execute_command("move to end of current word");

                break;
            case 's':editor.set_cmd('s');
                editor.execute_command("save file");

                break;
            case 'l':editor.set_cmd('l');
                editor.execute_command("load file");

                break;
            case'|':editor.set_cmd('|');

                break;
            case 'r':editor.indent(true);
                editor.execute_command("increase indent");

                break;
            case 't':editor.indent(false);
                editor.execute_command("decrease indent");

                break;
            case'j':
                editor.join_lines();
                editor.execute_command("join current with next line");

                break;
            case 'c':
                editor.set_cmd('c');

                break;
            case 'h':
                editor.get_history();

                break;
            case '1':
                editor.get_prev_cmd();
                break;
            case '2':
                editor.get_nex_cmd();
                break;
            case'/':
                editor.set_cmd('/');
                editor.execute_command("pattern searching");

                break;
            case'N':
                editor.find_prev();
                editor.execute_command("previous pattern searching");

                break;
            case'n':
                editor.find_next();
                editor.execute_command("next pattern searching");

                break;
            case':':
                editor.set_cmd(':');

                break;
            default: break;
            }
        }
    }
}

