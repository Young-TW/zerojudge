#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <algorithm>
#include <set>
#include <cctype>

using namespace std;

struct File {
    string name;
    bool isFolder;
    map<string, File*> children;
    File* parent;

    File(string n, bool isF, File* p) : name(n), isFolder(isF), parent(p) {}
};

File* root;
File* current;
File* clipboard = nullptr;
bool isCut = false;

void show() {
    cout << current->name << ":" << endl;
    vector<string> folders, datas;
    for (auto& child : current->children) {
        if (child.second->isFolder) {
            folders.push_back(child.first);
        } else {
            datas.push_back(child.first);
        }
    }
    sort(folders.begin(), folders.end());
    sort(datas.begin(), datas.end());

    if (folders.empty() && datas.empty()) {
        cout << "-(None)" << endl;
    } else {
        for (string& name : folders) {
            cout << "-" << name << " FOLD" << endl;
        }
        for (string& name : datas) {
            cout << "-" << name << " DATA" << endl;
        }
    }
    cout << endl;
}

void create(string name, string format) {
    if (current->children.find(name) != current->children.end()) {
        return;
    }
    bool isFolder = (format == "FOLD");
    current->children[name] = new File(name, isFolder, current);
}

void copy(string name) {
    if (current->children.find(name) == current->children.end()) {
        return;
    }
    clipboard = current->children[name];
    isCut = false;
}

void cut(string name) {
    if (current->children.find(name) == current->children.end()) {
        return;
    }
    clipboard = current->children[name];
    isCut = true;
}

File* deepCopy(File* file, File* parent) {
    File* newFile = new File(file->name, file->isFolder, parent);
    for (auto& child : file->children) {
        newFile->children[child.first] = deepCopy(child.second, newFile);
    }
    return newFile;
}

void pasta() {
    if (clipboard == nullptr) {
        return;
    }
    if (current->children.find(clipboard->name) != current->children.end()) {
        return;
    }
    File* newFile;
    if (isCut) {
        newFile = clipboard;
        newFile->parent->children.erase(newFile->name);
        newFile->parent = current;
    } else {
        newFile = deepCopy(clipboard, current);
    }
    current->children[newFile->name] = newFile;
    clipboard = nullptr;
}

void move(string name) {
    if (current->children.find(name) == current->children.end() || !current->children[name]->isFolder) {
        return;
    }
    current = current->children[name];
}

void returnCmd() {
    if (current->parent == nullptr) {
        return;
    }
    current = current->parent;
}

int main() {
    root = new File("C", true, nullptr);
    current = root;

    string cmd;
    while (cin >> cmd) {
        if (cmd == "show") {
            show();
        } else if (cmd == "create") {
            string name, format;
            cin >> name >> format;
            create(name, format);
        } else if (cmd == "copy") {
            string name;
            cin >> name;
            copy(name);
        } else if (cmd == "cut") {
            string name;
            cin >> name;
            cut(name);
        } else if (cmd == "pasta") {
            pasta();
        } else if (cmd == "move") {
            string name;
            cin >> name;
            move(name);
        } else if (cmd == "return") {
            returnCmd();
        }
    }

    return 0;
}
