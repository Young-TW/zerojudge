#include <iostream>
#include <string>
#include <stack>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    while (cin >> n && n) {
        for (int i = 0; i < n; ++i) {
            string s;
            cin >> s;
            
            string ans = "";
            int dep = 0;
            bool valid = true;
            stack<char> st;
            
            for (char c : s) {
                if (c == '(' || c == '[' || c == '{') {
                    st.push(c);
                    dep++;
                    if (dep >= 2) {
                        ans += c;
                    }
                } else {
                    if (st.empty()) {
                        valid = false;
                        break;
                    }
                    char top = st.top();
                    st.pop();
                    if ((c == ')' && top != '(') || 
                        (c == ']' && top != '[') || 
                        (c == '}' && top != '{')) {
                        valid = false;
                        break;
                    }
                    if (dep >= 2) {
                        ans += c;
                    }
                    dep--;
                }
            }
            
            if (valid && dep == 0) {
                if (ans.empty()) {
                    cout << "Product Broken!!\n";
                } else {
                    cout << ans << "\n";
                }
            } else {
                cout << "Product Broken!!\n";
            }
        }
    }
    
    return 0;
}
