#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int p, q, r, m;
    while (cin >> p >> q >> r >> m) {
        int N = p + q + r;
        vector<int> val(N + 1, 0);
        vector<int> delay(N + 1, 0);
        vector<int> in_degree(N + 1, 0);
        vector<vector<int>> adj(N + 1);
        vector<vector<int>> in_vals(N + 1);
        vector<int> gate_type(N + 1, 0);

        for (int i = 1; i <= p; ++i) {
            cin >> val[i];
        }
        for (int i = 1; i <= q; ++i) {
            cin >> gate_type[p + i];
        }

        for (int i = 0; i < m; ++i) {
            int u, v;
            cin >> u >> v;
            adj[u].push_back(v);
            in_degree[v]++;
        }

        queue<int> que;
        for (int i = 1; i <= p; ++i) {
            if (in_degree[i] == 0) {
                que.push(i);
            }
        }

        while (!que.empty()) {
            int u = que.front();
            que.pop();

            for (int v : adj[u]) {
                in_vals[v].push_back(val[u]);
                delay[v] = max(delay[v], delay[u]);
                if (--in_degree[v] == 0) {
                    if (v > p && v <= p + q) { // logic gate
                        if (gate_type[v] == 1) { // AND
                            val[v] = in_vals[v][0] & in_vals[v][1];
                        } else if (gate_type[v] == 2) { // OR
                            val[v] = in_vals[v][0] | in_vals[v][1];
                        } else if (gate_type[v] == 3) { // XOR
                            val[v] = in_vals[v][0] ^ in_vals[v][1];
                        } else if (gate_type[v] == 4) { // NOT
                            val[v] = !in_vals[v][0];
                        }
                        delay[v]++;
                    } else if (v > p + q) { // output port
                        val[v] = in_vals[v][0];
                    }
                    que.push(v);
                }
            }
        }

        int max_delay = 0;
        for (int i = p + q + 1; i <= N; ++i) {
            max_delay = max(max_delay, delay[i]);
        }

        cout << max_delay << "\n";
        for (int i = p + q + 1; i <= N; ++i) {
            cout << val[i] << (i == N ? "" : " ");
        }
        cout << "\n";
    }

    return 0;
}
