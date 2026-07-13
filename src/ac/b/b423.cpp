#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int X, Y, TYPE, DIFF;
    while (cin >> X >> Y >> TYPE >> DIFF) {
        int W, H;
        if (!(cin >> W >> H)) break;

        vector<vector<vector<int>>> img(H, vector<vector<int>>(W, vector<int>(4)));
        for (int i = 0; i < H; ++i) {
            for (int j = 0; j < W; ++j) {
                for (int k = 0; k < 4; ++k) {
                    cin >> img[i][j][k];
                }
            }
        }

        if (X >= 0 && X < W && Y >= 0 && Y < H && (TYPE == 0 || TYPE == 1)) {
            int R = img[Y][X][0];
            int G = img[Y][X][1];
            int B = img[Y][X][2];
            
            long long diff_sq = 0;
            bool can_erase = (DIFF >= 0);
            if (can_erase) {
                diff_sq = static_cast<long long>(DIFF) * DIFF;
            }

            auto check = [&](int r, int g, int b) {
                if (!can_erase) return false;
                long long dr = r - R;
                long long dg = g - G;
                long long db = b - B;
                return dr * dr + dg * dg + db * db <= diff_sq;
            };

            if (TYPE == 0) {
                for (int i = 0; i < H; ++i) {
                    for (int j = 0; j < W; ++j) {
                        if (check(img[i][j][0], img[i][j][1], img[i][j][2])) {
                            img[i][j][3] = 0;
                        }
                    }
                }
            } else if (TYPE == 1) {
                vector<vector<bool>> visited(H, vector<bool>(W, false));
                queue<pair<int, int>> q;
                
                if (check(img[Y][X][0], img[Y][X][1], img[Y][X][2])) {
                    q.push({Y, X});
                    visited[Y][X] = true;
                }
                
                int dx[] = {0, 0, 1, -1};
                int dy[] = {1, -1, 0, 0};

                while (!q.empty()) {
                    auto curr = q.front();
                    q.pop();
                    int y = curr.first;
                    int x = curr.second;
                    
                    img[y][x][3] = 0;

                    for (int i = 0; i < 4; ++i) {
                        int ny = y + dy[i];
                        int nx = x + dx[i];
                        if (ny >= 0 && ny < H && nx >= 0 && nx < W && !visited[ny][nx]) {
                            if (check(img[ny][nx][0], img[ny][nx][1], img[ny][nx][2])) {
                                visited[ny][nx] = true;
                                q.push({ny, nx});
                            }
                        }
                    }
                }
            }
        }

        cout << W << " " << H << "\n";
        for (int i = 0; i < H; ++i) {
            for (int j = 0; j < W; ++j) {
                for (int k = 0; k < 4; ++k) {
                    cout << img[i][j][k];
                    if (k < 3 || j < W - 1) cout << " ";
                }
            }
            cout << "\n";
        }
    }

    return 0;
}
