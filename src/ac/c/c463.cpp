#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    while (cin >> n) {
        vector<vector<int>> child(n + 1);
        vector<char> hasParent(n + 1, 0);

        for (int i = 1; i <= n; ++i) {
            int k; cin >> k;
            child[i].reserve(k);
            for (int j = 0; j < k; ++j) {
                int x; cin >> x;
                child[i].push_back(x);
                hasParent[x] = 1;
            }
        }

        int root = 1;
        for (int i = 1; i <= n; ++i) {
            if (!hasParent[i]) { root = i; break; }
        }

        vector<int> height(n + 1, 0);
        long long total = 0;

        vector<pair<int, bool>> st;
        st.reserve(2 * n);
        st.emplace_back(root, false);

        while (!st.empty()) {
            auto [v, processed] = st.back();
            st.pop_back();
            if (processed) {
                int h = 0;
                for (int c : child[v]) {
                    if (height[c] + 1 > h) h = height[c] + 1;
                }
                height[v] = h;
                total += h;
            } else {
                st.emplace_back(v, true);
                for (int c : child[v]) st.emplace_back(c, false);
            }
        }

        cout << root << '\n' << total << '\n';
    }
    return 0;
}
