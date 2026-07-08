#include <bits/stdc++.h>
using namespace std;

int main() {
    int N, Q;
    scanf("%d %d", &N, &Q);
    vector<vector<int>> adj(N + 1);
    for (int i = 0; i < N - 1; i++) {
        int A, B;
        scanf("%d %d", &A, &B);
        adj[A].push_back(B);
        adj[B].push_back(A);
    }

    for (int i = 0; i < Q; i++) {
        int X, K;
        scanf("%d %d", &X, &K);
        if (K >= N) {
            printf("%d\n", N);
            continue;
        }
        vector<int> dist(N + 1, -1);
        queue<int> bfs;
        bfs.push(X);
        dist[X] = 0;
        int ans = X;
        while (!bfs.empty()) {
            int u = bfs.front(); bfs.pop();
            if (dist[u] > K) continue;
            ans = max(ans, u);
            for (int v : adj[u]) {
                if (dist[v] == -1) {
                    dist[v] = dist[u] + 1;
                    bfs.push(v);
                }
            }
        }
        printf("%d\n", ans);
    }
    return 0;
}
