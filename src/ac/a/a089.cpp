#include <iostream>
#include <string>
#include <cstdlib>
using namespace std;

const int N = 30005;
int fa[N], dist[N], sz[N]; // dist[i]: #ships between i and its parent (exclusive of i, inclusive chain down); sz[i]: subtree size at root

int find(int x) {
    if (fa[x] == x) return x;
    int rt = find(fa[x]);
    dist[x] += dist[fa[x]];
    fa[x] = rt;
    return rt;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    for (int i = 1; i < N; ++i) { fa[i] = i; dist[i] = 0; sz[i] = 1; }

    int T;
    if (!(cin >> T)) return 0;
    string op;
    while (T--) {
        cin >> op;
        int i, j;
        cin >> i >> j;
        if (op == "M") {
            int ri = find(i), rj = find(j);
            if (ri != rj) {
                fa[ri] = rj;
                dist[ri] = sz[rj];
                sz[rj] += sz[ri];
            }
        } else { // C
            int ri = find(i), rj = find(j);
            if (ri != rj) cout << -1 << '\n';
            else cout << abs(dist[i] - dist[j]) - 1 << '\n';
        }
    }
    return 0;
}
