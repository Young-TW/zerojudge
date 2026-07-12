#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void solve() {
    int N;
    cin >> N;
    vector<long long> d(N + 1, 0);
    for (int i = 2; i <= N; ++i) {
        cin >> d[i];
    }
    vector<vector<pair<int, int>>> adj(N + 1);
    for (int i = 0; i < N - 1; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }

    vector<int> parent(N + 1, 0);
    vector<long long> w_to_parent(N + 1, 0);
    vector<int> q;
    q.reserve(N);
    q.push_back(1);
    parent[1] = -1;
    for (int i = 0; i < q.size(); ++i) {
        int u = q[i];
        for (auto edge : adj[u]) {
            int v = edge.first;
            int w = edge.second;
            if (parent[v] == 0) {
                parent[v] = u;
                w_to_parent[v] = w;
                q.push_back(v);
            }
        }
    }

    vector<long long> S(N + 1, 0);
    vector<long long> D(N + 1, 0);

    for (int i = N - 1; i >= 0; --i) {
        int u = q[i];
        vector<pair<long long, long long>> children; // (B, C)
        for (auto edge : adj[u]) {
            int v = edge.first;
            int w = edge.second;
            if (v != parent[u]) {
                long long C = S[v] + 2LL * w;
                long long B = D[v] - w;
                children.push_back({B, C});
            }
        }
        
        if (children.empty()) {
            S[u] = 0;
            D[u] = d[u];
        } else {
            sort(children.begin(), children.end());
            long long current_S = 0;
            long long current_D = d[u];
            for (auto child : children) {
                long long B = child.first;
                long long C = child.second;
                current_D = max(current_D, B - current_S);
                current_S += C;
            }
            S[u] = current_S;
            D[u] = current_D;
        }
    }

    cout << D[1] + S[1] << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int T;
    while (cin >> T) {
        while (T--) {
            solve();
        }
    }
    return 0;
}
