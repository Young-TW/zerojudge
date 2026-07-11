#include <iostream>
#include <string>
#include <stack>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    if (!(cin >> n)) return 0;
    string dummy;
    getline(cin, dummy);
    
    while (n--) {
        string s;
        if (!getline(cin, s)) {
            break;
        }
        
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
            cout << "Yes\n";
        } else {
            cout << "No\n";
        }
    }
    
    return 0;
}
