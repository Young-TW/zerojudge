#include <iostream>
#include <string>
#include <vector>
#include <queue>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    long long L, W, H;
    while (cin >> L >> W >> H) {
        long long total = L * W * H;
        string s, t;
        s.reserve(total);
        while ((long long)s.size() < total && cin >> t) s += t;
        vector<char> vis(total, 0);
        long long layer = L * W;
        long long best = 0;
        queue<long long> q;
        for (long long st = 0; st < total; ++st) {
            if (s[st] != '0' || vis[st]) continue;
            long long cnt = 0;
            vis[st] = 1;
            q.push(st);
            while (!q.empty()) {
                long long cur = q.front(); q.pop();
                ++cnt;
                long long h = cur / layer;
                long long rem = cur - h * layer;
                long long i = rem / W;
                long long j = rem - i * W;
                if (h + 1 < H) { long long nx = cur + layer; if (!vis[nx] && s[nx] == '0') { vis[nx] = 1; q.push(nx); } }
                if (h > 0)     { long long nx = cur - layer; if (!vis[nx] && s[nx] == '0') { vis[nx] = 1; q.push(nx); } }
                if (i + 1 < L) { long long nx = cur + W;     if (!vis[nx] && s[nx] == '0') { vis[nx] = 1; q.push(nx); } }
                if (i > 0)     { long long nx = cur - W;     if (!vis[nx] && s[nx] == '0') { vis[nx] = 1; q.push(nx); } }
                if (j + 1 < W) { long long nx = cur + 1;     if (!vis[nx] && s[nx] == '0') { vis[nx] = 1; q.push(nx); } }
                if (j > 0)     { long long nx = cur - 1;     if (!vis[nx] && s[nx] == '0') { vis[nx] = 1; q.push(nx); } }
            }
            if (cnt > best) best = cnt;
        }
        cout << best << '\n';
    }
    return 0;
}
