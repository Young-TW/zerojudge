#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    vector<string> lines;
    string s;
    while (getline(cin, s)) {
        lines.push_back(s);
    }
    
    vector<int> indent_stack;
    indent_stack.push_back(0);
    bool prev_colon = false;
    
    for (int i = 0; i < (int)lines.size(); ++i) {
        const string& line = lines[i];
        int indent = 0;
        while (indent < (int)line.length() && line[indent] == ' ') {
            indent++;
        }
        
        bool is_colon = !line.empty() && line.back() == ':';
        
        if (indent > indent_stack.back()) {
            if (prev_colon) {
                indent_stack.push_back(indent);
            } else {
                cout << "line " << (i + 1) << "\n";
                cout << line << "\n";
                cout << "unexpected indent\n";
                return 0;
            }
        } else if (indent == indent_stack.back()) {
            if (prev_colon) {
                cout << "line " << (i + 1) << "\n";
                cout << line << "\n";
                cout << "expected an indented block\n";
                return 0;
            }
        } else { // indent < indent_stack.back()
            if (prev_colon) {
                cout << "line " << (i + 1) << "\n";
                cout << line << "\n";
                cout << "expected an indented block\n";
                return 0;
            } else {
                bool found = false;
                for (int j = (int)indent_stack.size() - 1; j >= 0; --j) {
                    if (indent_stack[j] == indent) {
                        found = true;
                        break;
                    }
                    if (indent_stack[j] < indent) {
                        break;
                    }
                }
                if (found) {
                    while (indent_stack.back() > indent) {
                        indent_stack.pop_back();
                    }
                } else {
                    cout << "line " << (i + 1) << "\n";
                    cout << line << "\n";
                    cout << "unindent does not match any outer indentation level\n";
                    return 0;
                }
            }
        }
        
        prev_colon = is_colon;
    }
    
    cout << "Indention OK\n";
    return 0;
}
