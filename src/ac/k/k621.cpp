#include <iostream>
#include <string>
#include <stack>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    string s;
    while (cin >> s) {
        stack<char> st;
        bool valid = true;
        for (char c : s) {
            if (c == '(' || c == '[') {
                st.push(c);
            } else if (c == ')') {
                if (st.empty() || st.top() != '(') {
                    valid = false;
                    break;
                }
                st.pop();
            } else if (c == ']') {
                if (st.empty() || st.top() != '[') {
                    valid = false;
                    break;
                }
                st.pop();
            }
        }
        if (valid && st.empty()) {
            cout << "Right\n";
        } else {
            cout << "Wrong\n";
        }
    }
    
    return 0;
}
