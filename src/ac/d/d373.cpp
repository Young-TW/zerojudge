#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <algorithm>
#include <cctype>
using namespace std;

static bool isNumTok(const string &s) {
    if (s.empty()) return false;
    size_t i = 0;
    if (s[0] == '-' || s[0] == '+') i = 1;
    if (i == s.size()) return false;
    for (; i < s.size(); ++i)
        if (!isdigit((unsigned char)s[i])) return false;
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    auto readNum = [&](int &out) -> bool {
        string s;
        while (cin >> s) {
            if (isNumTok(s)) { out = stoi(s); return true; }
        }
        return false;
    };

    int W, H;
    while (readNum(W)) {
        if (!readNum(H)) break;

        vector<vector<int>> diff(W + 2, vector<int>(H + 2, 0));
        int mbx1 = 0, mby1 = 0, mbx2 = -1, mby2 = -1;
        int cbx1 = 0, cby1 = 0, cbx2 = -1, cby2 = -1;

        auto addRect = [&](int x1, int y1, int x2, int y2) {
            if (x1 > x2) swap(x1, x2);
            if (y1 > y2) swap(y1, y2);
            if (x2 < 0 || y2 < 0 || x1 >= W || y1 >= H) return;
            x1 = max(x1, 0); y1 = max(y1, 0);
            x2 = min(x2, W - 1); y2 = min(y2, H - 1);
            diff[x1][y1] += 1;
            diff[x2 + 1][y1] -= 1;
            diff[x1][y2 + 1] -= 1;
            diff[x2 + 1][y2 + 1] += 1;
        };

        string t;
        while (cin >> t) {
            if (t == ".mb") {
                readNum(mbx1); readNum(mby1); readNum(mbx2); readNum(mby2);
            } else if (t == ".cb") {
                readNum(cbx1); readNum(cby1); readNum(cbx2); readNum(cby2);
            } else if (t == ".bb") {
                string u;
                while (cin >> u) {
                    if (u == ".be") break;
                    if (isNumTok(u)) {
                        int x1 = stoi(u), y1, x2, y2;
                        readNum(y1); readNum(x2); readNum(y2);
                        addRect(x1, y1, x2, y2);
                    }
                }
                break;
            }
            // ignore unknown tokens
        }

        // 2D prefix sum: diff[x][y] > 0 means blocked
        for (int x = 0; x < W; ++x) {
            for (int y = 0; y < H; ++y) {
                if (x > 0) diff[x][y] += diff[x - 1][y];
                if (y > 0) diff[x][y] += diff[x][y - 1];
                if (x > 0 && y > 0) diff[x][y] -= diff[x - 1][y - 1];
            }
        }

        auto normRect = [&](int &x1, int &y1, int &x2, int &y2) {
            if (x1 > x2) swap(x1, x2);
            if (y1 > y2) swap(y1, y2);
            x1 = max(x1, 0); y1 = max(y1, 0);
            x2 = min(x2, W - 1); y2 = min(y2, H - 1);
        };
        normRect(mbx1, mby1, mbx2, mby2);
        normRect(cbx1, cby1, cbx2, cby2);

        const int N = W * H;
        vector<char> cheese(N, 0);
        for (int x = cbx1; x <= cbx2; ++x)
            for (int y = cby1; y <= cby2; ++y)
                cheese[y * W + x] = 1;

        vector<int> dist(N, -1);
        queue<int> q;
        for (int x = mbx1; x <= mbx2; ++x) {
            for (int y = mby1; y <= mby2; ++y) {
                if (diff[x][y] > 0) continue;
                int id = y * W + x;
                if (dist[id] < 0) {
                    dist[id] = 0;
                    q.push(id);
                }
            }
        }

        int ans = -1;
        const int dx[4] = {1, -1, 0, 0};
        const int dy[4] = {0, 0, 1, -1};
        while (!q.empty()) {
            int id = q.front(); q.pop();
            int d = dist[id];
            if (cheese[id]) { ans = d; break; }
            int x = id % W, y = id / W;
            for (int k = 0; k < 4; ++k) {
                int nx = x + dx[k], ny = y + dy[k];
                if (nx < 0 || nx >= W || ny < 0 || ny >= H) continue;
                if (diff[nx][ny] > 0) continue;
                int nid = ny * W + nx;
                if (dist[nid] >= 0) continue;
                dist[nid] = d + 1;
                q.push(nid);
            }
        }

        if (ans < 0) cout << "no path\n";
        else cout << ans << '\n';
    }
    return 0;
}
