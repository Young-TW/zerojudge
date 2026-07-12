#include <iostream>
#include <string>
#include <stack>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int T;
    if (!(cin >> T)) return 0;
    cin.ignore();
    
    while (T--) {
        string s;
        getline(cin, s);
        stack<char> st;
        bool valid = true;
        
        for (char c : s) {
            if (c == '(' || c == '[' || c == '<' || c == '{') {
                st.push(c);
            } else if (c == ')' || c == ']' || c == '>' || c == '}') {
                if (st.empty()) {
                    valid = false;
                    break;
                }
                char top = st.top();
                st.pop();
                if ((c == ')' && top != '(') ||
                    (c == ']' && top != '[') ||
                    (c == '>' && top != '<') ||
                    (c == '}' && top != '{')) {
                    valid = false;
                    break;
                }
            }
        }
        
        if (valid && st.empty()) {
            cout << "Y\n";
        } else {
            cout << "N\n";
        }
    }
    
    return 0;
}
