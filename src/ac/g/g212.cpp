#include <iostream>
#include <algorithm>

using namespace std;

const int MAX_COORD = 200000;
const int OFFSET = 200000;
const int MAX_NODES = 400005;

int parent[MAX_NODES];
long long cntX[MAX_NODES];
long long cntY[MAX_NODES];

int find(int i) {
    return parent[i] == i ? i : parent[i] = find(parent[i]);
}

void init() {
    for (int i = 1; i <= MAX_COORD; ++i) {
        parent[i] = i;
        cntX[i] = 1;
        cntY[i] = 0;
    }
    for (int i = MAX_COORD + 1; i <= 2 * MAX_COORD; ++i) {
        parent[i] = i;
        cntX[i] = 0;
        cntY[i] = 1;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    while (cin >> n) {
        init();
        long long ans = 0;
        for (int i = 0; i < n; ++i) {
            int x, y;
            cin >> x >> y;
            int u = x;
            int v = y + OFFSET;
            int ru = find(u);
            int rv = find(v);
            if (ru != rv) {
                ans += cntX[ru] * cntY[rv] + cntX[rv] * cntY[ru];
                if (cntX[ru] + cntY[ru] < cntX[rv] + cntY[rv]) {
                    swap(ru, rv);
                }
                parent[rv] = ru;
                cntX[ru] += cntX[rv];
                cntY[ru] += cntY[rv];
            }
            cout << ans << "\n";
        }
    }
    return 0;
}
