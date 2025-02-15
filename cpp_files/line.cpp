#include "line.h"

node::node(char ch) : letter(ch), next(nullptr), prev(nullptr) {}  

line::line(const string& con) : head(nullptr), tail(nullptr), cursor_node(nullptr), cursor_position(0), cursor_at_head(true), cursor_at_tail(false), content("") {
    for (char ch : con) {
        insert_char(ch);
    }
}

line::line() : head(nullptr), tail(nullptr), cursor_node(nullptr), cursor_position(0), cursor_at_head(true), cursor_at_tail(false), content("") {}

void line::insert_char(char ch) {
    node* new_node = new node(ch);

    if (head == nullptr) {
        head = new_node;
        tail = new_node;
        cursor_node = new_node;
        cursor_at_head = false;
        cursor_at_tail = true;
        cursor_position = 1;
    }
    else if (cursor_at_head) {
        new_node->next = head;
        head->prev = new_node;
        head = new_node;
        cursor_node = new_node;
        cursor_at_head = false;
        cursor_at_tail = false;
        cursor_position = 1;
    }
    else {
        new_node->next = cursor_node ? cursor_node->next : nullptr;
        new_node->prev = cursor_node;
        if (cursor_node->next != nullptr) {
            cursor_node->next->prev = new_node;
        }
        else {
            tail = new_node;
            cursor_at_tail = true;
        }
        cursor_node->next = new_node;
        cursor_node = new_node;
        cursor_position++;
    }
}

bool line::move_right() {
    if (head == nullptr) {
        return true;
    }
    else if (cursor_node == nullptr) {
        cursor_node = head;
        cursor_at_head = false;
        cursor_position = 1;
    }
    else if (cursor_node->next != nullptr) {
        cursor_node = cursor_node->next;
        cursor_position++;
        cursor_at_tail = false;
    }
    else {
        cursor_at_head = false;
        cursor_at_tail = true;
        return true;
    }
    return false;
}

bool line::move_left() {
    if (head == nullptr) {
        return true;
    }
    else if (cursor_node == head) {
        cursor_node = nullptr;
        cursor_at_head = true;
        cursor_at_tail = false;
        cursor_position = 0;
    }
    else if (cursor_node == nullptr) {
        cursor_node = nullptr;
        cursor_at_head = true;
        cursor_at_tail = false;
        return true;
    }
    else if (cursor_node->prev != nullptr) {
        cursor_node = cursor_node->prev;
        cursor_position--;
        cursor_at_tail = false;
    }
    return false;
}

void line::display(bool display_cursor) const {
    node* temp = head;
    if (display_cursor && cursor_at_head && cursor_node == nullptr) {
        cout << "|";
    }
    while (temp != nullptr) {
        cout << temp->letter;
        if (display_cursor && temp == cursor_node) {
            cout << "|";
        }
        temp = temp->next;
    }
    if (display_cursor && cursor_node == nullptr && !cursor_at_head) {
        cout << "|";
    }
}

node* line::get_cursor() const {
    return cursor_node;
}

node* line::get_head() {
    return head;
}

node* line::get_tail() {
    return tail;
}

void line::delete_after_cursor() {
    node* temp;
    if (cursor_node == nullptr) {
        temp = head;
        head = nullptr;
        tail = nullptr;
    }
    else {
        temp = cursor_node->next;
        cursor_node->next = nullptr;
        tail = cursor_node;
    }

    while (temp) {
        node* to_delete = temp;
        temp = temp->next;
        delete to_delete;
    }
}

void line::del_at_cursor() {
    if (cursor_node == head) {
        node* to_delete = head;
        head = head->next;
        if (head != nullptr) {
            head->prev = nullptr;
        }
        else {
            tail = nullptr;
        }
        cursor_node = nullptr;
        cursor_at_head = true;
        cursor_at_tail = false;
        cursor_position = 0;
        delete to_delete;
    }
    else {
        node* to_delete = cursor_node;
        if (cursor_node->prev != nullptr) {
            cursor_node->prev->next = cursor_node->next;
        }
        if (cursor_node->next != nullptr) {
            cursor_node->next->prev = cursor_node->prev;
            cursor_node = cursor_node->prev;
        }
        else {
            cursor_node = cursor_node->prev;
            tail = cursor_node;
            cursor_at_tail = true;
        }
        cursor_position--;
        delete to_delete;
    }
}

int line::cursor_p() {
    return cursor_position;
}

void line::cursor_at_end() {
    if (head != nullptr) {
        if (cursor_node == nullptr) {
            cursor_node = head;
            cursor_at_head = false;
            cursor_position = 1;
        }
        while (cursor_node->next != nullptr) {
            cursor_node = cursor_node->next;
            cursor_position++;
        }
        cursor_at_tail = true;
    }
    else {
        cursor_node = nullptr;
        cursor_at_head = true;
        cursor_position = 0;
        cursor_at_tail = false;
    }
}

void line::move_cursor_at_zero_position() {
    cursor_node = nullptr;
    cursor_at_head = true;
    cursor_at_tail = false;
    cursor_position = 0;
}

void line::yank(string& buffer) {
    buffer.clear();
    if (!head) {
        return;
    }
    node* temp = head;
    while (temp) {
        buffer += temp->letter;
        temp = temp->next;
    }
}

void line::yank_m(string& buffer) {
    if (!head) {
        return;
    }
    node* temp = head;
    while (temp) {
        buffer += temp->letter;
        temp = temp->next;
    }
}

void line::paste_after(const string& buffer) {
    for (char ch : buffer) insert_char(ch);
}

void line::paste_before(const string& buffer) {
    if (cursor_node) { move_left(); }
    paste_after(buffer);
}

string line::get_content() {
    content.clear();
    node* n = head;
    while (n) {
        content += n->letter;
        n = n->next;
    }
    return content;
}

string line::get_content_pre(size_t num) {
    content.clear();
    node* n = head;
    int nu = 0;
    while (n) {
        if (nu == num) {
            break;
        }
        content += n->letter;
        n = n->next;
        nu++;
    }
    return content;
}

string line::get_content_next(size_t num) {
    content.clear();
    node* n = head;
    int nu = 0;
    while (n) {
        if (nu > num) {
            content += n->letter;
        }
        n = n->next;
        nu++;
    }
    return content;
}

bool line::if_tail() {
    return cursor_node == tail;
}

bool line::if_head() {
    return cursor_node == head;
}

void line::move_to_nex_word() {
    while (cursor_node && is_word_character(cursor_node->letter)) {
        if (!if_tail()) {
            cursor_node = cursor_node->next;
            cursor_position++;
        }
        else {
            break;
        }
    }
    while (cursor_node && is_punctuation(cursor_node->letter)) {
        cursor_node = cursor_node->next;
        cursor_position++;
    }
    while (cursor_node && !is_word_character(cursor_node->letter)) {
        cursor_node = cursor_node->next;
        cursor_position++;
    }
}

void line::move_to_pre_word() {
    while (cursor_node && is_word_character(cursor_node->letter)) {
        if (!if_head()) {
            cursor_node = cursor_node->prev;
            cursor_position++;
        }
        else {
            break;
        }
    }
    while (cursor_node && is_punctuation(cursor_node->letter)) {
        cursor_node = cursor_node->prev;
        cursor_position++;
    }
    while (cursor_node && !is_word_character(cursor_node->letter)) {
        cursor_node = cursor_node->prev;
        cursor_position++;
    }
}

void line::word_end() {
    if (!(cursor_node->next == nullptr || cursor_node->prev == nullptr) ||
        !(is_word_character(cursor_node->next->letter) && !is_word_character(cursor_node->prev->letter))) {
        if (cursor_node) {
            while (cursor_node->next) {
                if (is_word_character(cursor_node->letter)) {
                    cursor_node = cursor_node->next;
                    cursor_position++;
                }
                else {
                    break;
                }
            }
        }
    }
}

void line::delete_line() {
    if (!head) {
        cout << "no line to delete" << endl;
        return;
    }
    node* n = head;
    while (n != nullptr) {
        node* temp = n;
        n = n->next;
        delete temp;
    }
    head = tail = cursor_node = nullptr;
    cursor_at_head = true;
    cursor_at_tail = false;
    cursor_position = 0;
    content.clear();
}

void line::set_content(const string& newContent) {
    content = newContent;
}

void line::indent_r(bool r) {
    move_cursor_at_zero_position();
    if (r) {
        insert_char('\t');
    }
    else {
        del_at_cursor();
    }
}

void line::join(const string& other) {
    cursor_node = tail;
    for (char ch : other) {
        insert_char(ch);
    }
}
bool line::is_word_character(char ch) {
    return isalnum(ch);
}

bool line::is_punctuation(char ch) {
    return ispunct(ch);
}

