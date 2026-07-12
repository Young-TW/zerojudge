#include <iostream>
#include <vector>
#include <stack>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    while (cin >> n) {
        vector<int> target(n);
        for (int i = 0; i < n; ++i) {
            cin >> target[i];
        }
        
        stack<int> st;
        int next_train = 1;
        bool possible = true;
        
        for (int i = 0; i < n; ++i) {
            if (!st.empty() && st.top() == target[i]) {
                st.pop();
            } else if (next_train <= target[i]) {
                while (next_train <= target[i]) {
                    st.push(next_train);
                    ++next_train;
                }
                st.pop();
            } else {
                possible = false;
                break;
            }
        }
        
        if (possible) {
            cout << "Yes\n";
        } else {
            cout << "No\n";
        }
    }
    
    return 0;
}
