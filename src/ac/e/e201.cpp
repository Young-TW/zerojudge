#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    while (cin >> T) {
        while (T--) {
            int N;
            cin >> N;
            vector<ll> deadline(N + 1, 0);          // d[1] = 0
            for (int i = 2; i <= N; ++i) cin >> deadline[i];

            vector<vector<pair<int,int>>> adj(N + 1);
            for (int i = 0; i < N - 1; ++i) {
                int a, b, w;
                cin >> a >> b >> w;
                adj[a].push_back({b, w});
                adj[b].push_back({a, w});
            }

            // parent and order (BFS/DFS)
            vector<int> parent(N + 1, -1);
            vector<int> wpar(N + 1, 0);          // weight to parent
            vector<int> order;
            order.reserve(N);
            order.push_back(1);
            parent[1] = 0;
            for (size_t i = 0; i < order.size(); ++i) {
                int u = order[i];
                for (auto &e : adj[u]) {
                    int v = e.first, w = e.second;
                    if (parent[v] == -1) {
                        parent[v] = u;
                        wpar[v] = w;
                        order.push_back(v);
                    }
                }
            }

            vector<ll> len(N + 1, 0);   // travelling length of subtree
            vector<ll> extra(N + 1, 0); // minimal additional waiting

            // process bottom‑up
            for (int idx = N - 1; idx >= 0; --idx) {
                int u = order[idx];
                vector<pair<ll,ll>> childs; // (B , C)
                for (auto &e : adj[u]) {
                    int v = e.first;
                    if (parent[v] == u) {
                        ll C = len[v] + 2LL * wpar[v];
                        ll B = extra[v] - wpar[v];
                        childs.push_back({B, C});
                    }
                }
                sort(childs.begin(), childs.end(),
                     [](const pair<ll,ll>& a, const pair<ll,ll>& b){
                         return a.first < b.first;
                     });

                ll cur = 0;          // travelled inside processed children
                ll need = 0;         // required extra waiting so far
                for (auto &bc : childs) {
                    ll B = bc.first, C = bc.second;
                    need = max(need, B - cur);
                    cur += C;
                }
                need = max(need, deadline[u] - cur);
                if (need < 0) need = 0;

                len[u] = cur;
                extra[u] = need;
            }

            cout << (len[1] + extra[1]) << '\n';
        }
    }
    return 0;
}
