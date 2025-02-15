#include "file_manager.h"


using namespace std;

FileManager::FileManager() : currentFileName(""), modified(false) {}

bool FileManager::loadFile(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        return false;
    }
    currentFileName = filename;
    content.clear();
    string line;
    while (getline(file, line)) {
        content += line + '\n';
    }
    modified = false;
    file.close();
    return true;
}

bool FileManager::saveFile(const string& filename) {
    ofstream file(filename);
    if (!file.is_open()) {
        return false;
    }
    file << content;
    currentFileName = filename;
    modified = false;
    file.close();
    return true;
}

bool FileManager::hasUnsavedChanges() const {
    return modified;
}

void FileManager::markAsModified() {
    modified = true;
}

string FileManager::getCurrentFileName() const {
    return currentFileName.empty() ? "untitled" : currentFileName;
}

void FileManager::set_content(const string& newContent) {
    content = newContent;
    markAsModified();
}

string FileManager::get_content() const {
    return content;
}
