#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <queue>
#include <map>
#include <algorithm>

using namespace std;

struct Node {
    string name;
    bool is_folder;
    Node* parent;
    map<string, Node*> children;
    Node(string n, bool folder, Node* p) : name(n), is_folder(folder), parent(p) {}
};

Node* clone(Node* node, Node* new_parent) {
    Node* new_node = new Node(node->name, node->is_folder, new_parent);
    if (node->is_folder) {
        for (auto& kv : node->children) {
            Node* child_clone = clone(kv.second, new_node);
            new_node->children[kv.first] = child_clone;
        }
    }
    return new_node;
}

void add(Node* parent, const string& type, const string& name) {
    if (!parent->is_folder) return;
    if (parent->children.count(name)) {
        parent->children.erase(name);
    }
    bool is_folder = (type == "folder");
    Node* child = new Node(name, is_folder, parent);
    parent->children[name] = child;
}

void delete_target(Node* parent, const string& name) {
    if (!parent->is_folder) return;
    auto it = parent->children.find(name);
    if (it != parent->children.end()) {
        parent->children.erase(it);
    }
}

void cut(Node* parent, const string& name, Node*& clipboard) {
    if (!parent->is_folder) return;
    auto it = parent->children.find(name);
    if (it != parent->children.end()) {
        Node* target = it->second;
        clipboard = clone(target, nullptr);
        parent->children.erase(it);
    }
}

void copy(Node* parent, const string& name, Node*& clipboard) {
    if (!parent->is_folder) return;
    auto it = parent->children.find(name);
    if (it != parent->children.end()) {
        clipboard = clone(it->second, nullptr);
    }
}

void paste(Node* parent, Node* clipboard) {
    if (!parent->is_folder || clipboard == nullptr) return;
    Node* new_node = clone(clipboard, parent);
    parent->children[new_node->name] = new_node;
}

Node* find_folder(Node* root, const string& name) {
    if (root->name == name) return root;
    queue<Node*> q;
    q.push(root);
    while (!q.empty()) {
        Node* cur = q.front(); q.pop();
        if (cur->is_folder) {
            for (auto& kv : cur->children) {
                Node* child = kv.second;
                if (child->is_folder) {
                    if (child->name == name) return child;
                    q.push(child);
                }
            }
        }
    }
    return nullptr;
}

void process_command(const string& line, Node* root, Node*& clipboard) {
    vector<string> tokens;
    stringstream ss(line);
    string token;
    while (ss >> token) {
        tokens.push_back(token);
    }
    if (tokens.empty()) return;

    int action_idx = -1;
    string action;
    for (int i = 0; i < (int)tokens.size(); i++) {
        if (tokens[i] == "add" || tokens[i] == "delete" || tokens[i] == "cut" || tokens[i] == "copy" || tokens[i] == "paste") {
            action_idx = i;
            action = tokens[i];
            break;
        }
    }
    if (action_idx == -1) return;

    string executor_name;
    for (int i = 0; i < action_idx; i++) {
        if (i > 0) executor_name += " ";
        executor_name += tokens[i];
    }
    if (executor_name == "fire manager") executor_name = "file manager";

    vector<string> args;
    for (int i = action_idx + 1; i < (int)tokens.size(); i++) {
        args.push_back(tokens[i]);
    }

    Node* executor = find_folder(root, executor_name);
    if (!executor) return;

    if (action == "add") {
        if (args.empty()) return;
        string type, name;
        if (args.size() >= 2 && (args[0] == "file" || args[0] == "folder")) {
            type = args[0];
            name = args[1];
        } else {
            type = "file";
            name = args[0];
        }
        add(executor, type, name);
    } else if (action == "delete") {
        if (args.empty()) return;
        delete_target(executor, args[0]);
    } else if (action == "cut") {
        if (args.empty()) return;
        cut(executor, args[0], clipboard);
    } else if (action == "copy") {
        if (args.empty()) return;
        copy(executor, args[0], clipboard);
    } else if (action == "paste") {
        paste(executor, clipboard);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string line;
    while (true) {
        vector<string> commands;
        if (!getline(cin, line)) break;
        if (line == "stop") {
            string s;
            if (!getline(cin, s)) break;
            Node* root = new Node("file manager", true, nullptr);
            Node* clipboard = nullptr;
            Node* target_folder = find_folder(root, s);
            if (target_folder) {
                vector<pair<string, string>> items;
                for (auto& kv : target_folder->children) {
                    Node* child = kv.second;
                    items.push_back({child->name, child->is_folder ? "folder" : "file"});
                }
                sort(items.begin(), items.end(), [](const pair<string,string>& a, const pair<string,string>& b) {
                    return a.first < b.first;
                });
                for (auto& item : items) {
                    cout << item.second << " " << item.first << "\n";
                }
            }
            continue;
        } else {
            commands.push_back(line);
        }

        while (getline(cin, line)) {
            if (line == "stop") break;
            commands.push_back(line);
        }

        string s;
        if (!getline(cin, s)) break;

        Node* root = new Node("file manager", true, nullptr);
        Node* clipboard = nullptr;

        for (const string& cmd : commands) {
            process_command(cmd, root, clipboard);
        }

        Node* target_folder = find_folder(root, s);
        if (target_folder) {
            vector<pair<string, string>> items;
            for (auto& kv : target_folder->children) {
                Node* child = kv.second;
                items.push_back({child->name, child->is_folder ? "folder" : "file"});
            }
            sort(items.begin(), items.end(), [](const pair<string,string>& a, const pair<string,string>& b) {
                return a.first < b.first;
            });
            for (auto& item : items) {
                cout << item.second << " " << item.first << "\n";
            }
        }
    }
    return 0;
}
