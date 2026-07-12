#include <iostream>
#include <vector>

using namespace std;

int parent[1005];

int find(int i) {
    if (parent[i] == i)
        return i;
    return parent[i] = find(parent[i]);
}

void unite(int i, int j) {
    int root_i = find(i);
    int root_j = find(j);
    if (root_i != root_j) {
        parent[root_i] = root_j;
    }
}

struct Point {
    long long x, y, z;
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int T;
    if (!(cin >> T)) return 0;
    while (T--) {
        int n;
        long long h, r;
        cin >> n >> h >> r;
        vector<Point> pts(n);
        for (int i = 0; i <= n + 1; ++i) {
            parent[i] = i;
        }
        for (int i = 0; i < n; ++i) {
            cin >> pts[i].x >> pts[i].y >> pts[i].z;
            if (pts[i].z - r <= 0) {
                unite(i, n);
            }
            if (pts[i].z + r >= h) {
                unite(i, n + 1);
            }
            for (int j = 0; j < i; ++j) {
                long long dx = pts[i].x - pts[j].x;
                long long dy = pts[i].y - pts[j].y;
                long long dz = pts[i].z - pts[j].z;
                if (dx < 0) dx = -dx;
                if (dy < 0) dy = -dy;
                if (dz < 0) dz = -dz;
                unsigned long long dist_sq = (unsigned long long)dx * dx + (unsigned long long)dy * dy + (unsigned long long)dz * dz;
                unsigned long long limit = 4ULL * r * r;
                if (dist_sq <= limit) {
                    unite(i, j);
                }
            }
        }
        if (find(n) == find(n + 1)) {
            cout << "Yes\n";
        } else {
            cout << "No\n";
        }
    }
    return 0;
}
