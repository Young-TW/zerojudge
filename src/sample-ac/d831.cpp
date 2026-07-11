#include <cstdio>
#include <algorithm>

using namespace std;

const int MAXN = 1000001;
int parent[MAXN];
int sz[MAXN];
int vis[MAXN];
int current_timestamp = 0;

int find_set(int v) {
    int root = v;
    while (root != parent[root]) {
        root = parent[root];
    }
    while (v != root) {
        int next = parent[v];
        parent[v] = root;
        v = next;
    }
    return root;
}

void union_sets(int a, int b) {
    a = find_set(a);
    b = find_set(b);
    if (a != b) {
        if (sz[a] < sz[b])
            swap(a, b);
        parent[b] = a;
        sz[a] += sz[b];
    }
}

int main() {
    int n, m;
    while (scanf("%d %d", &n, &m) == 2) {
        current_timestamp++;
        int max_sz = 1;
        for (int i = 0; i < m; i++) {
            int u, v;
            scanf("%d %d", &u, &v);
            if (vis[u] != current_timestamp) {
                vis[u] = current_timestamp;
                parent[u] = u;
                sz[u] = 1;
            }
            if (vis[v] != current_timestamp) {
                vis[v] = current_timestamp;
                parent[v] = v;
                sz[v] = 1;
            }
            union_sets(u, v);
            int root = find_set(u);
            if (sz[root] > max_sz) {
                max_sz = sz[root];
            }
        }
        printf("%d\n", max_sz);
    }
    return 0;
}
