#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Edge {
    int u, v;
    long long w;
    bool operator<(const Edge& other) const {
        return w > other.w;
    }
};

const int MAXN = 200005;
int fa[MAXN];
int d[MAXN];

int find(int x) {
    if (fa[x] == x) return x;
    int root = find(fa[x]);
    d[x] ^= d[fa[x]];
    fa[x] = root;
    return root;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int N, M;
    while (cin >> N >> M) {
        for (int i = 1; i <= N; ++i) {
            fa[i] = i;
            d[i] = 0;
        }
        vector<Edge> edges(M);
        for (int i = 0; i < M; ++i) {
            cin >> edges[i].u >> edges[i].v >> edges[i].w;
        }
        sort(edges.begin(), edges.end());
        
        long long ans = 0;
        for (int i = 0; i < M; ++i) {
            int u = edges[i].u;
            int v = edges[i].v;
            long long w = edges[i].w;
            int fu = find(u);
            int fv = find(v);
            if (fu == fv) {
                if (d[u] == d[v]) {
                    ans = w;
                    break;
                }
            } else {
                fa[fu] = fv;
                d[fu] = d[u] ^ d[v] ^ 1;
            }
        }
        cout << ans << "\n";
    }
    return 0;
}
