#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> parent;
vector<int> rnk;

void init(int n) {
    parent.resize(n + 1);
    rnk.assign(n + 1, 0);
    for (int i = 1; i <= n; ++i) {
        parent[i] = i;
    }
}

int find(int i) {
    if (parent[i] != i)
        parent[i] = find(parent[i]);
    return parent[i];
}

void union_set(int i, int j) {
    int root_i = find(i);
    int root_j = find(j);
    if (root_i != root_j) {
        if (rnk[root_i] < rnk[root_j])
            parent[root_i] = root_j;
        else if (rnk[root_i] > rnk[root_j])
            parent[root_j] = root_i;
        else {
            parent[root_j] = root_i;
            rnk[root_i]++;
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int N, M;
    while (cin >> N >> M) {
        init(N);
        vector<int> max_d(N + 1, 0);
        for (int i = 0; i < M; ++i) {
            int u, v, d;
            cin >> u >> v >> d;
            if (u >= 1 && u <= N && v >= 1 && v <= N) {
                max_d[u] = max(max_d[u], d);
                max_d[v] = max(max_d[v], d);
                union_set(u, v);
            }
        }
        vector<int> block_max(N + 1, 0);
        for (int i = 1; i <= N; ++i) {
            int root = find(i);
            block_max[root] = max(block_max[root], max_d[i]);
        }
        long long ans = 0;
        for (int i = 1; i <= N; ++i) {
            ans += block_max[find(i)];
        }
        cout << ans << "\n";
    }
    return 0;
}
