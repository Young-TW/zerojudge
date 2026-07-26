#include <bits/stdc++.h>
using namespace std;

struct Node {
    long long d;
    int x, y;
    bool operator<(Node const& other) const {
        return d > other.d;               // for min‑heap
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    while (cin >> n >> m) {
        vector<vector<int>> a(n, vector<int>(m));
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < m; ++j)
                cin >> a[i][j];

        const long long INF = (1LL << 60);
        vector<vector<long long>> dist(n, vector<long long>(m, INF));
        priority_queue<Node> pq;

        dist[0][0] = 0;
        pq.push({0, 0, 0});

        const int dx[4] = {1, -1, 0, 0};
        const int dy[4] = {0, 0, 1, -1};

        long long answer = -1;
        while (!pq.empty()) {
            Node cur = pq.top(); pq.pop();
            if (cur.d != dist[cur.x][cur.y]) continue;
            if (cur.x == n - 1 && cur.y == m - 1) {
                answer = cur.d;
                break;
            }
            for (int dir = 0; dir < 4; ++dir) {
                int nx = cur.x + dx[dir];
                int ny = cur.y + dy[dir];
                if (nx < 0 || nx >= n || ny < 0 || ny >= m) continue;
                long long nd = max(cur.d + 1LL, (long long)a[nx][ny]);
                if (nd < dist[nx][ny]) {
                    dist[nx][ny] = nd;
                    pq.push({nd, nx, ny});
                }
            }
        }
        cout << answer << '\n';
    }
    return 0;
}
