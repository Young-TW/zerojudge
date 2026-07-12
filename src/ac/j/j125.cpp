#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int n;
vector<vector<int>> h;
int dx[] = {0, 0, 1, -1};
int dy[] = {1, -1, 0, 0};

vector<vector<bool>> vis;
vector<vector<int>> dist;

bool check(int D) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            vis[i][j] = false;
        }
    }
    queue<pair<int, int>> q;
    q.push({0, 0});
    vis[0][0] = true;
    while (!q.empty()) {
        pair<int, int> curr = q.front();
        q.pop();
        int x = curr.first;
        int y = curr.second;
        if (x == n - 1 && y == n - 1) return true;
        for (int i = 0; i < 4; ++i) {
            int nx = x + dx[i];
            int ny = y + dy[i];
            if (nx >= 0 && nx < n && ny >= 0 && ny < n && !vis[nx][ny]) {
                int diff = h[x][y] - h[nx][ny];
                if (diff < 0) diff = -diff;
                if (diff <= D) {
                    vis[nx][ny] = true;
                    q.push({nx, ny});
                }
            }
        }
    }
    return false;
}

int getShortestPath(int D) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            dist[i][j] = -1;
        }
    }
    queue<pair<int, int>> q;
    q.push({0, 0});
    dist[0][0] = 0;
    while (!q.empty()) {
        pair<int, int> curr = q.front();
        q.pop();
        int x = curr.first;
        int y = curr.second;
        if (x == n - 1 && y == n - 1) return dist[x][y];
        for (int i = 0; i < 4; ++i) {
            int nx = x + dx[i];
            int ny = y + dy[i];
            if (nx >= 0 && nx < n && ny >= 0 && ny < n && dist[nx][ny] == -1) {
                int diff = h[x][y] - h[nx][ny];
                if (diff < 0) diff = -diff;
                if (diff <= D) {
                    dist[nx][ny] = dist[x][y] + 1;
                    q.push({nx, ny});
                }
            }
        }
    }
    return -1;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    while (cin >> n) {
        h.assign(n, vector<int>(n));
        vis.assign(n, vector<bool>(n, false));
        dist.assign(n, vector<int>(n, -1));
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                cin >> h[i][j];
            }
        }
        int L = 0, R = 1000000;
        int ans_D = R;
        while (L <= R) {
            int mid = L + (R - L) / 2;
            if (check(mid)) {
                ans_D = mid;
                R = mid - 1;
            } else {
                L = mid + 1;
            }
        }
        cout << ans_D << "\n";
        cout << getShortestPath(ans_D) << "\n";
    }
    return 0;
}
