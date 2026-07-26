#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long long n, L;
    while (cin >> n >> L) {
        vector<long long> pos(n + 2);
        vector<long long> h(n + 2, 0);
        // sentinels
        pos[0] = 0;
        pos[n + 1] = L;

        for (int i = 1; i <= n; ++i) cin >> pos[i];
        for (int i = 1; i <= n; ++i) cin >> h[i];

        vector<int> left(n + 2), right(n + 2);
        vector<char> removed(n + 2, 0);
        for (int i = 0; i <= n + 1; ++i) {
            left[i] = i - 1;
            right[i] = i + 1;
        }

        auto cutable = [&](int i) -> bool {
            if (i <= 0 || i > n) return false;
            if (pos[i] - h[i] >= pos[left[i]]) return true;   // fall left
            if (pos[i] + h[i] <= pos[right[i]]) return true;  // fall right
            return false;
        };

        queue<int> q;
        for (int i = 1; i <= n; ++i) {
            if (cutable(i)) q.push(i);
        }

        long long cnt = 0;
        long long maxH = 0;

        while (!q.empty()) {
            int i = q.front(); q.pop();
            if (removed[i]) continue;
            if (!cutable(i)) continue;          // neighbours changed meanwhile

            // cut tree i
            removed[i] = 1;
            ++cnt;
            if (h[i] > maxH) maxH = h[i];

            int li = left[i];
            int ri = right[i];
            right[li] = ri;
            left[ri] = li;

            // neighbours may become cutable now
            if (li >= 1 && li <= n && !removed[li] && cutable(li)) q.push(li);
            if (ri >= 1 && ri <= n && !removed[ri] && cutable(ri)) q.push(ri);
        }

        cout << cnt << '\n' << maxH << '\n';
    }
    return 0;
}
