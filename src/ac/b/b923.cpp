#include <iostream>
#include <stack>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    while (cin >> n) {
        stack<int> st;
        for (int i = 0; i < n; ++i) {
            int op;
            cin >> op;
            if (op == 1) {
                if (!st.empty()) {
                    st.pop();
                }
            } else if (op == 2) {
                if (!st.empty()) {
                    cout << st.top() << "\n";
                }
            } else if (op == 3) {
                int x;
                cin >> x;
                st.push(x);
            }
        }
    }
    
    return 0;
}
