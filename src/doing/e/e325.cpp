#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m, q;
    while (cin >> n >> m >> q) {
        vector<int> grid(n * m);
        for (int i = 0; i < n; ++i) {
            int base = i * m;
            for (int j = 0; j < m; ++j) {
                grid[base + j] = base + j + 1;
            }
        }
        for (int k = 0; k < q; ++k) {
            int x, y;
            cin >> x >> y;
            --x; --y;
            int val = grid[x * m + y];
            cout << val << '\n';
            if (y < m - 1) {
                memmove(&grid[x * m + y], &grid[x * m + y + 1],
                        static_cast<size_t>(m - y - 1) * sizeof(int));
            }
            for (int i = x; i < n - 1; ++i) {
                grid[i * m + (m - 1)] = grid[(i + 1) * m + (m - 1)];
            }
            grid[(n - 1) * m + (m - 1)] = val;
        }
    }
    return 0;
}
