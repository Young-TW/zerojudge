#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <cstring>
#include <functional>
#include <utility>

using namespace std;

int dc[8] = {-2, -2, -1, -1, 1, 1, 2, 2};
int dr[8] = {1, -1, 2, -2, 2, -2, 1, -1};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    string start_str, end_str;
    while (cin >> start_str >> end_str) {
        string block_str;
        bool is_block[8][8];
        memset(is_block, 0, sizeof(is_block));

        while (cin >> block_str && block_str != "xx") {
            int c = block_str[0] - 'a';
            int r = '8' - block_str[1];
            is_block[c][r] = true;
        }

        int start_c = start_str[0] - 'a';
        int start_r = '8' - start_str[1];
        int end_c = end_str[0] - 'a';
        int end_r = '8' - end_str[1];

        int dist[8][8];
        memset(dist, -1, sizeof(dist));
        queue<pair<int, int>> q;
        q.push({end_c, end_r});
        dist[end_c][end_r] = 0;

        while (!q.empty()) {
            auto curr = q.front();
            q.pop();
            int c = curr.first;
            int r = curr.second;

            for (int i = 0; i < 8; ++i) {
                int nc = c + dc[i];
                int nr = r + dr[i];
                if (nc >= 0 && nc < 8 && nr >= 0 && nr < 8 && !is_block[nc][nr] && dist[nc][nr] == -1) {
                    dist[nc][nr] = dist[c][r] + 1;
                    q.push({nc, nr});
                }
            }
        }

        int min_steps = dist[start_c][start_r];
        cout << "The shortest solution is " << min_steps << " move(s).\n";

        if (min_steps != -1) {
            vector<pair<int, int>> path;
            path.push_back({start_c, start_r});

            function<void(int, int, int)> dfs = [&](int c, int r, int steps_left) {
                if (steps_left == 0) {
                    if (c == end_c && r == end_r) {
                        cout << "Solution:";
                        for (auto p : path) {
                            cout << " " << char('a' + p.first) << char('8' - p.second);
                        }
                        cout << "\n";
                    }
                    return;
                }

                for (int i = 0; i < 8; ++i) {
                    int nc = c + dc[i];
                    int nr = r + dr[i];
                    if (nc >= 0 && nc < 8 && nr >= 0 && nr < 8 && !is_block[nc][nr] && dist[nc][nr] == steps_left - 1) {
                        path.push_back({nc, nr});
                        dfs(nc, nr, steps_left - 1);
                        path.pop_back();
                    }
                }
            };

            dfs(start_c, start_r, min_steps);
        }
    }

    return 0;
}
