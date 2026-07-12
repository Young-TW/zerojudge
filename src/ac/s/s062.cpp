#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;

const int MAXN = 300005;
const int MAXA = 300005;

vector<int> pos[MAXA];
int parent[MAXN];
int last_occurrence[MAXA];

int find(int x) {
    if (parent[x] != x) {
        parent[x] = find(parent[x]);
    }
    return parent[x];
}

void unite(int x, int y) {
    x = find(x);
    y = find(y);
    if (x != y) {
        parent[y] = x;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q;
    cin >> n >> q;

    vector<int> a(n + 1);
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
    }

    for (int i = 1; i <= n; ++i) {
        parent[i] = i;
    }

    memset(last_occurrence, 0, sizeof(last_occurrence));
    for (int i = 1; i <= n; ++i) {
        int num = a[i];
        for (int bit = 0; bit < 19; ++bit) {
            if (num & (1 << bit)) {
                if (last_occurrence[bit] != 0) {
                    unite(last_occurrence[bit], i);
                }
            }
        }
        for (int bit = 0; bit < 19; ++bit) {
            if (num & (1 << bit)) {
                last_occurrence[bit] = i;
            }
        }
    }

    while (q--) {
        int x, y;
        cin >> x >> y;
        if (find(x) == find(y)) {
            cout << "Shi\n";
        } else {
            cout << "Fou\n";
        }
    }

    return 0;
}
