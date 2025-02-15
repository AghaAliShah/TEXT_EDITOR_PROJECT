#pragma once
#pragma once
#include<string>
#include <fstream>
using namespace std;


class FileManager {
private:
    string currentFileName;
    bool modified;
    string content;


public:
    FileManager();
    bool loadFile(const string& filename);
    bool saveFile(const string& filename);
    bool hasUnsavedChanges() const;
    void markAsModified();
    string getCurrentFileName() const;
    void set_content(const string& newContent);
    string get_content() const;
};

