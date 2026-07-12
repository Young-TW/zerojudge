#include <iostream>
#include <string>
#include <sstream>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    string line;
    while (getline(cin, line)) {
        stringstream ss(line);
        string token;
        string expr = "";
        string current_val = "";
        bool first = true;
        string pending_op = "";
        
        while (ss >> token) {
            if (token == "and" || token == "or") {
                pending_op = token;
                if (token == "and") {
                    expr += "&&";
                } else {
                    expr += "||";
                }
            } else {
                if (first) {
                    current_val = token;
                    expr = token;
                    first = false;
                } else {
                    for (size_t i = 0; i < current_val.length(); ++i) {
                        if (pending_op == "and") {
                            current_val[i] = (current_val[i] == '1' && token[i] == '1') ? '1' : '0';
                        } else if (pending_op == "or") {
                            current_val[i] = (current_val[i] == '1' || token[i] == '1') ? '1' : '0';
                        }
                    }
                    expr += token;
                }
            }
        }
        
        if (!first) {
            cout << expr << " = " << current_val << "\n";
        }
    }
    
    return 0;
}
