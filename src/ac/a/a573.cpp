#include <cstdio>
#include <vector>
#include <unordered_map>

using namespace std;

int parent[60005];

int find(int x) {
    while (parent[x] != x) {
        parent[x] = parent[parent[x]];
        x = parent[x];
    }
    return x;
}

void unite(int a, int b) {
    a = find(a);
    b = find(b);
    if (a != b) parent[a] = b;
}

int main() {
    int t;
    scanf("%d", &t);
    while (t--) {
        int n, r;
        scanf("%d %d", &n, &r);

        vector<int> xs(n), ys(n);
        for (int i = 0; i < n; i++) {
            scanf("%d %d", &xs[i], &ys[i]);
        }

        for (int i = 0; i < n; i++) parent[i] = i;

        long long cellSize = 2LL * r;
        long long cellSizeSq = cellSize * cellSize;

        // Grid: cell size = 2R. Two intersecting circles must be in same or adjacent cells.
        unordered_map<long long, vector<int>> grid;
        grid.reserve(n * 2);

        const long long OFFSET = 100000LL;
        const long long BIG = 200001LL;

        for (int i = 0; i < n; i++) {
            long long cx = (xs[i] >= 0) ? ((long long)xs[i] / cellSize)
                                        : ((long long)xs[i] - cellSize + 1) / cellSize;
            long long cy = (ys[i] >= 0) ? ((long long)ys[i] / cellSize)
                                        : ((long long)ys[i] - cellSize + 1) / cellSize;

            for (int dx = -1; dx <= 1; dx++) {
                for (int dy = -1; dy <= 1; dy++) {
                    long long nx = cx + dx;
                    long long ny = cy + dy;
                    long long key = (nx + OFFSET) * BIG + (ny + OFFSET);
                    auto it = grid.find(key);
                    if (it != grid.end()) {
                        for (size_t k = 0; k < it->second.size(); k++) {
                            int j = it->second[k];
                            long long ddx = (long long)xs[i] - xs[j];
                            long long ddy = (long long)ys[i] - ys[j];
                            if (ddx * ddx + ddy * ddy <= cellSizeSq) {
                                unite(i, j);
                            }
                        }
                    }
                }
            }

            long long key = (cx + OFFSET) * BIG + (cy + OFFSET);
            grid[key].push_back(i);
        }

        int components = 0;
        for (int i = 0; i < n; i++) {
            if (find(i) == i) components++;
        }
        printf("%d\n", components);
    }
    return 0;
}
