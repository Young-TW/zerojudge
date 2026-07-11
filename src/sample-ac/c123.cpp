#include <iostream>
#include <vector>
#include <stack>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    while (cin >> N && N) {
        vector<int> target(N);
        while (cin >> target[0] && target[0]) {
            for (int i = 1; i < N; ++i) {
                cin >> target[i];
            }

            stack<int> st;
            int current = 1;
            bool possible = true;
            for (int i = 0; i < N; ++i) {
                while (current <= N && (st.empty() || st.top() != target[i])) {
                    st.push(current);
                    current++;
                }
                if (!st.empty() && st.top() == target[i]) {
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
        cout << "\n";
    }

    return 0;
}
