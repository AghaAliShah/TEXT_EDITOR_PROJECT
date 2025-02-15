#pragma once
#include <iostream>
#include <cctype>
using namespace std;
#include <string>

struct node {
    char letter;
    node* next;
    node* prev;
    node(char ch);
};

class line {
private:
    node* head;
    node* tail;
    node* cursor_node;
    bool cursor_at_head;
    bool cursor_at_tail;
    int cursor_position;
    string content;

    bool is_word_character(char c);
    bool is_punctuation(char c);

public:
    line(const string& con);
    line();
    

    void insert_char(char ch);
    bool move_right();
    bool move_left();
    void display(bool display_cursor) const;
    node* get_cursor() const;
    node* get_head();
    node* get_tail();
    void delete_after_cursor();
    void del_at_cursor();
    int cursor_p();
    void cursor_at_end();
    void move_cursor_at_zero_position();
    void yank(string& buffer);
    void yank_m(string& buffer);
    void paste_after(const string& buffer);
    void paste_before(const string& buffer);
    string get_content();
    string get_content_pre(size_t num);
    string get_content_next(size_t num);
    bool if_tail();
    bool if_head();
    void move_to_nex_word();
    void move_to_pre_word();
    void word_end();
    void delete_line();  
    void set_content(const string& new_content);
    void indent_r(bool r);
    void join(const string& other);
};

