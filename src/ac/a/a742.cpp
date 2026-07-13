#include <iostream>
#include <cstring>

using namespace std;

const int MAXN = 1005;
int blocked_right[MAXN][MAXN];
int blocked_down[MAXN][MAXN];
int dist[MAXN * MAXN];
int q[MAXN * MAXN];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int N, M, X0, Y0, X1, Y1, K;
    int test_id = 0;
    while (cin >> N >> M >> X0 >> Y0 >> X1 >> Y1 >> K) {
        test_id++;
        for (int i = 0; i < K; ++i) {
            int X2, Y2, X3, Y3;
            cin >> X2 >> Y2 >> X3 >> Y3;
            if (X2 == X3) {
                for (int y = Y2; y < Y3; ++y) {
                    blocked_right[X2][y] = test_id;
                }
            } else {
                for (int x = X2; x < X3; ++x) {
                    blocked_down[x][Y2] = test_id;
                }
            }
        }

        memset(dist, -1, sizeof(int) * (size_t)N * M);
        
        int head = 0, tail = 0;
        int start = X0 * M + Y0;
        int target = X1 * M + Y1;
        
        q[tail++] = start;
        dist[start] = 0;

        int dx[] = {0, 0, 1, -1};
        int dy[] = {1, -1, 0, 0};

        while (head < tail) {
            int curr = q[head++];
            if (curr == target) {
                break;
            }
            int x = curr / M;
            int y = curr % M;

            for (int i = 0; i < 4; ++i) {
                int nx = x + dx[i];
                int ny = y + dy[i];
                if (nx >= 0 && nx < N && ny >= 0 && ny < M) {
                    int next = nx * M + ny;
                    if (dist[next] == -1) {
                        bool can_move = false;
                        if (i == 0) { // right
                            if (blocked_right[x][y] != test_id) can_move = true;
                        } else if (i == 1) { // left
                            if (blocked_right[x][y-1] != test_id) can_move = true;
                        } else if (i == 2) { // down
                            if (blocked_down[x][y] != test_id) can_move = true;
                        } else { // up
                            if (blocked_down[x-1][y] != test_id) can_move = true;
                        }

                        if (can_move) {
                            dist[next] = dist[curr] + 1;
                            q[tail++] = next;
                        }
                    }
                }
            }
        }

        if (dist[target] != -1) {
            cout << dist[target] << "\n";
        } else {
            cout << 10080 << "\n";
        }
    }

    return 0;
}
