#include <iostream>
#include <stack>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int N;
    while (cin >> N) {
        stack<int> st;
        for (int i = 0; i < N; ++i) {
            int k;
            cin >> k;
            if (k == 1) {
                int x;
                cin >> x;
                st.push(x);
            } else if (k == 2) {
                if (st.empty()) {
                    cout << -1 << '\n';
                } else {
                    cout << st.top() << '\n';
                }
            } else if (k == 3) {
                if (!st.empty()) {
                    st.pop();
                }
            }
        }
    }
    
    return 0;
}
