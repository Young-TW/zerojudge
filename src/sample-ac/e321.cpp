#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

struct Loop {
    char var;
    bool is_active;
    bool contributes;
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    while (cin >> t) {
        while (t--) {
            int L;
            string complexity_str;
            cin >> L >> complexity_str;
            int expected = 0;
            size_t pos = complexity_str.find('^');
            if (pos != string::npos) {
                expected = stoi(complexity_str.substr(pos + 1));
            }
            
            vector<Loop> stack;
            bool in_stack[26] = {false};
            int current_complexity = 0;
            int max_complexity = 0;
            bool err = false;
            
            for (int j = 0; j < L; ++j) {
                string op;
                cin >> op;
                if (op == "F") {
                    string i, x, y;
                    cin >> i >> x >> y;
                    if (err) continue;
                    char var = i[0];
                    if (in_stack[var - 'a']) {
                        err = true;
                        continue;
                    }
                    in_stack[var - 'a'] = true;
                    
                    bool parent_active = stack.empty() ? true : stack.back().is_active;
                    bool x_is_n = (x == "n");
                    bool y_is_n = (y == "n");
                    
                    bool x_le_y;
                    if (x_is_n && y_is_n) x_le_y = true;
                    else if (x_is_n && !y_is_n) x_le_y = false;
                    else if (!x_is_n && y_is_n) x_le_y = true;
                    else x_le_y = (stoi(x) <= stoi(y));
                    
                    bool is_active = parent_active && x_le_y;
                    bool contributes = is_active && !x_is_n && y_is_n;
                    
                    if (is_active && contributes) {
                        current_complexity++;
                        max_complexity = max(max_complexity, current_complexity);
                    }
                    stack.push_back({var, is_active, contributes});
                } else {
                    if (err) continue;
                    if (stack.empty()) {
                        err = true;
                        continue;
                    }
                    Loop top = stack.back();
                    stack.pop_back();
                    in_stack[top.var - 'a'] = false;
                    if (top.is_active && top.contributes) {
                        current_complexity--;
                    }
                }
            }
            
            if (err || !stack.empty()) {
                cout << "ERR\n";
            } else {
                if (max_complexity == expected) {
                    cout << "Yes\n";
                } else {
                    cout << "No\n";
                }
            }
        }
    }
    return 0;
}
