#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    while (cin >> n >> m) {
        int total_cells = n * m;
        vector<int> grid(total_cells);
        vector<bool> visited(total_cells, false);

        int min_val = 2000000;
        int start_idx = -1;

        for (int i = 0; i < total_cells; ++i) {
            cin >> grid[i];
            if (grid[i] < min_val) {
                min_val = grid[i];
                start_idx = i;
            }
        }

        long long sum = 0;
        int curr = start_idx;

        int dr[] = {-1, 1, 0, 0};
        int dc[] = {0, 0, -1, 1};

        while (curr != -1) {
            visited[curr] = true;
            sum += grid[curr];

            int r = curr / m;
            int c = curr % m;

            int next_idx = -1;
            int min_next_val = 2000000;

            for (int i = 0; i < 4; ++i) {
                int nr = r + dr[i];
                int nc = c + dc[i];

                if (nr >= 0 && nr < n && nc >= 0 && nc < m) {
                    int n_idx = nr * m + nc;
                    if (!visited[n_idx]) {
                        if (grid[n_idx] < min_next_val) {
                            min_next_val = grid[n_idx];
                            next_idx = n_idx;
                        }
                    }
                }
            }

            curr = next_idx;
        }

        cout << sum << "\n";
    }

    return 0;
}
