#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int H, W;
    while (cin >> H >> W) {
        vector<string> grid(H);
        for (int i = 0; i < H; ++i) {
            cin >> grid[i];
        }

        int shapes[4][4][2] = {
            {{0, 0}, {0, 1}, {0, 2}, {1, 1}}, 
            {{0, 1}, {1, 0}, {1, 1}, {1, 2}}, 
            {{0, 0}, {1, 0}, {2, 0}, {1, 1}}, 
            {{0, 1}, {1, 1}, {2, 1}, {1, 0}}  
        };

        vector<vector<pair<int, int>>> results;

        for (int y = 0; y < H; ++y) {
            for (int x = 0; x < W; ++x) {
                for (int s = 0; s < 4; ++s) {
                    bool valid = true;
                    vector<pair<int, int>> cell;
                    for (int p = 0; p < 4; ++p) {
                        int nx = x + shapes[s][p][0];
                        int ny = y + shapes[s][p][1];
                        if (nx >= 0 && nx < W && ny >= 0 && ny < H && grid[ny][nx] == 'O') {
                            cell.push_back({nx, ny});
                        } else {
                            valid = false;
                            break;
                        }
                    }
                    if (valid) {
                        sort(cell.begin(), cell.end());
                        results.push_back(cell);
                    }
                }
            }
        }

        sort(results.begin(), results.end());

        cout << results.size() << "\n";
        for (const auto& cell : results) {
            for (const auto& p : cell) {
                cout << " (" << p.first << "," << p.second << ") ";
            }
            cout << "\n";
        }
    }

    return 0;
}
