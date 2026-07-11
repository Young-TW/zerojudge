#include <iostream>
#include <string>
#include <vector>

struct Node;

struct Entry {
    std::string key;
    bool is_object;
    std::string string_value;
    Node* object_value;
};

struct Node {
    std::vector<Entry> entries;
};

void print(Node* node, std::ostream& os) {
    os << '{';
    for (size_t i = 0; i < node->entries.size(); ++i) {
        if (i > 0) os << ',';
        const Entry& e = node->entries[i];
        os << '"' << e.key << '"' << ':';
        if (e.is_object) {
            print(e.object_value, os);
        } else {
            os << '"' << e.string_value << '"';
        }
    }
    os << '}';
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::string cmd;
    std::vector<Node*> stack;
    std::vector<Node*> all_nodes;
    Node* current_root = nullptr;
    while (std::cin >> cmd) {
        if (cmd == "insert") {
            std::string key_token, value_token;
            std::cin >> key_token >> value_token;
            std::string key = key_token.substr(1, key_token.size() - 2);
            if (stack.empty()) {
                Node* root = new Node;
                all_nodes.push_back(root);
                current_root = root;
                stack.push_back(root);
            }
            if (value_token == "newJSONObject") {
                Node* child = new Node;
                all_nodes.push_back(child);
                Entry e;
                e.key = key;
                e.is_object = true;
                e.object_value = child;
                stack.back()->entries.push_back(e);
                stack.push_back(child);
            } else {
                std::string value = value_token.substr(1, value_token.size() - 2);
                Entry e;
                e.key = key;
                e.is_object = false;
                e.string_value = value;
                stack.back()->entries.push_back(e);
            }
        } else if (cmd == "end") {
            if (!stack.empty()) {
                stack.pop_back();
                if (stack.empty()) {
                    print(current_root, std::cout);
                    std::cout << '\n';
                    current_root = nullptr;
                }
            }
        }
    }
    if (current_root != nullptr) {
        print(current_root, std::cout);
        std::cout << '\n';
    }
    for (Node* n : all_nodes) delete n;
    return 0;
}
