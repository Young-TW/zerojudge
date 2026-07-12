#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int R, C, a, b;
    while (cin >> R >> C >> a >> b) {
        vector<int> grid(R * C);
        for (int i = 0; i < R * C; ++i) {
            cin >> grid[i];
        }

        vector<int> dist(R * C, -1);
        vector<int> q;
        q.reserve(R * C);
        int head = 0;

        int start_idx = a * C + b;
        if (grid[start_idx] == 2) {
            cout << 0 << "\n";
            continue;
        }

        q.push_back(start_idx);
        dist[start_idx] = 0;

        int dr[] = {-1, 1, 0, 0};
        int dc[] = {0, 0, -1, 1};

        bool found = false;
        while (head < q.size()) {
            int idx = q[head++];
            int r = idx / C;
            int c = idx % C;

            for (int i = 0; i < 4; ++i) {
                int nr = r + dr[i];
                int nc = c + dc[i];

                if (nr >= 0 && nr < R && nc >= 0 && nc < C) {
                    int n_idx = nr * C + nc;
                    if (dist[n_idx] == -1 && grid[n_idx] != 1) {
                        dist[n_idx] = dist[idx] + 1;
                        if (grid[n_idx] == 2) {
                            cout << dist[n_idx] << "\n";
                            found = true;
                            break;
                        }
                        q.push_back(n_idx);
                    }
                }
            }
            if (found) break;
        }

        if (!found) {
            cout << "WAKUWAKU\n";
        }
    }

    return 0;
}
