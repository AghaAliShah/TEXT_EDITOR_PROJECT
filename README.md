# Text Editor - README

## Overview
This text editor is a lightweight, terminal-based application inspired by Vim. It supports basic and advanced text editing functionalities, including cursor movement, text manipulation, file operations, and command history. The editor is implemented in C++ and utilizes linked lists and vectors for efficient text management.

## Features
### 1. Text Editing Modes
- **Insert Mode**: Allows direct text entry.
- **Normal Mode**: Supports navigation and command execution.

### 2. Cursor Movement
- **Arrow Keys (↑, ↓, →, ←)**: Navigate within the text.
- **0 / $**: Jump to the start or end of the current line.
- **w / b / e**: Move by words.

### 3. Text Manipulation
- **Backspace**: Deletes the character before the cursor.
- **x**: Deletes the character under the cursor.
- **d**: Deletes the current line.
- **y**: Yanks (copies) the current line.
- **p / P**: Pastes the copied content after/before the current line.
- **r / t**: Indent/unindent the current line.
- **j**: Joins the current line with the next.

### 4. File Operations
- **s**: Save the file.
- **l**: Load a file.
- **|**: Set command for file management.

### 5. Search & Replace
- **/**: Search for a pattern.
- **n / N**: Find next/previous occurrence.

### 6. Command History
- **h**: View command history.
- **1 / 2**: Navigate through previous/next commands.

### 7. Exiting
- **q**: Quit the editor.

## Usage
1. Run the program.
2. Switch between Insert and Normal mode (`i` / `I` to enter Insert mode, `Esc` to return to Normal mode).
3. Use commands to edit, search, and manipulate text.
4. Save (`s`) or load (`l`) files as needed.
5. Exit with `q`.

## Requirements
- C++ Compiler
- Terminal with input handling support

## Notes
- The editor supports handling edge cases like empty lines, boundary conditions, and invalid commands.
- Enhancements include command execution tracking and error handling.

