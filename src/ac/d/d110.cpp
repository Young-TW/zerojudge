#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n;
    while (cin >> n) {
        vector<int> a(n + 1);
        for (int i = 1; i <= n; ++i) cin >> a[i];

        // min_suffix[i] = min_{j >= i} a[j]
        vector<int> min_suf(n + 2, n + 1);
        for (int i = n; i >= 1; --i) {
            min_suf[i] = min(a[i], min_suf[i + 1]);
        }

        // build graph
        vector<vector<int>> adj(n + 1);
        for (int i = 1; i <= n; ++i) {
            for (int j = i + 1; j <= n; ++j) {
                if (a[i] < a[j] && min_suf[j + 1] < a[i]) {
                    adj[i].push_back(j);
                    adj[j].push_back(i);
                }
            }
        }

        // bipartite coloring
        vector<int> color(n + 1, -1);
        bool ok = true;
        for (int i = 1; i <= n && ok; ++i) {
            if (color[i] == -1) {
                color[i] = 0;
                queue<int> q;
                q.push(i);
                while (!q.empty() && ok) {
                    int u = q.front(); q.pop();
                    for (int v : adj[u]) {
                        if (color[v] == -1) {
                            color[v] = color[u] ^ 1;
                            q.push(v);
                        } else if (color[v] == color[u]) {
                            ok = false;
                            break;
                        }
                    }
                }
            }
        }
        if (!ok) {
            cout << 0 << '\n';
            continue;
        }

        // simulation
        stack<int> s1, s2;
        vector<char> ans;
        int cur = 1, idx = 1;
        while (cur <= n) {
            if (idx <= n && color[idx] == 0 && (s1.empty() || a[idx] < s1.top())) {
                s1.push(a[idx]);
                ans.push_back('a');
                ++idx;
            } else if (!s1.empty() && s1.top() == cur) {
                s1.pop();
                ans.push_back('b');
                ++cur;
            } else if (idx <= n && color[idx] == 1 && (s2.empty() || a[idx] < s2.top())) {
                s2.push(a[idx]);
                ans.push_back('c');
                ++idx;
            } else if (!s2.empty() && s2.top() == cur) {
                s2.pop();
                ans.push_back('d');
                ++cur;
            } else {
                ok = false;
                break;
            }
        }
        if (!ok) {
            cout << 0 << '\n';
            continue;
        }

        // output
        for (size_t i = 0; i < ans.size(); ++i) {
            if (i) cout << ' ';
            cout << ans[i];
        }
        cout << '\n';
    }
    return 0;
}
