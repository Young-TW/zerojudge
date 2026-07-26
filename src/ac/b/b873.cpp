#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    if (!(cin >> T)) return 0;
    while (T--) {
        int N;
        cin >> N;
        vector<int> f(N + 1);
        for (int i = 1; i <= N; ++i) cin >> f[i];

        vector<char> state(N + 1, 0);   // 0 = unvisited, 1 = on stack, 2 = done
        vector<int> ans(N + 1, 0);      // -1 or 1

        for (int v = 1; v <= N; ++v) {
            if (state[v] != 0) continue;

            vector<int> stack;
            int cur = v;
            while (state[cur] == 0) {
                state[cur] = 1;
                stack.push_back(cur);
                cur = f[cur];
            }

            // cur is already visited
            if (state[cur] == 1) {               // a new cycle discovered
                int len = 1;
                int x = f[cur];
                while (x != cur) {
                    ++len;
                    x = f[x];
                }
                int cycleAns = (len == 1) ? -1 : 1;

                // assign answer to the whole cycle
                x = cur;
                do {
                    ans[x] = cycleAns;
                    state[x] = 2;
                    x = f[x];
                } while (x != cur);
            }

            // back‑propagation for the rest of the stack
            for (int i = (int)stack.size() - 1; i >= 0; --i) {
                int u = stack[i];
                if (state[u] == 2) continue;          // already part of a cycle
                ans[u] = ans[f[u]];
                state[u] = 2;
            }
        }

        int Q;
        cin >> Q;
        while (Q--) {
            int K;
            cin >> K;
            cout << ans[K] << '\n';
        }
    }
    return 0;
}
