#include <cstdio>
#include <iostream>
#include <cstring>
using namespace std;
using namespace std;

const int MAXN = 50005;
int parent[MAXN], rel[MAXN];

// rel[x]: relation of x to its parent. 0 = same kind, 1 = x eats parent, 2 = x eaten by parent.
int find(int x) {
    if (parent[x] == x) return x;
    int root = find(parent[x]);
    rel[x] = (rel[x] + rel[parent[x]]) % 3;
    parent[x] = root;
    return root;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int N, K;
    while (cin >> N >> K) {
        for (int i = 0; i <= N; i++) { parent[i] = i; rel[i] = 0; }
        int ans = 0;
        for (int i = 0; i < K; i++) {
            int D, X, Y;
            cin >> D >> X >> Y;
            if (X > N || Y > N) { ans++; continue; }
            if (D == 2 && X == Y) { ans++; continue; }
            int rx = find(X), ry = find(Y);
            if (D == 1) {
                if (rx == ry) {
                    if (rel[X] != rel[Y]) ans++;
                } else {
                    parent[rx] = ry;
                    rel[rx] = (rel[Y] - rel[X] + 3) % 3;
                }
            } else {
                if (rx == ry) {
                    if ((rel[X] - rel[Y] + 3) % 3 != 1) ans++;
                } else {
                    parent[rx] = ry;
                    rel[rx] = (rel[Y] - rel[X] + 1) % 3;
                }
            }
        }
        cout << ans << "\n";
    }
    return 0;
}
