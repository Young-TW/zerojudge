#include <bits/stdc++.h>
using namespace std;

using ll = long long;

bool can(const vector<ll>& h, int n, int k, int p, ll D) {
    if (k == 1) return (p <= n);               // always possible, D = 0
    int limit = n - k;                         // last possible start index
    if (limit < 0) return false;               // cannot form a single group

    vector<char> good(limit + 1, 0);

    if (k == 2) {
        for (int i = 0; i <= limit; ++i)
            good[i] = (h[i + 1] - h[i] <= D);
    } else {
        int win = k - 2;                        // window size on diff[]
        int diffSize = n - 2;
        vector<ll> diff(diffSize);
        for (int i = 0; i < diffSize; ++i) diff[i] = h[i + 2] - h[i];

        deque<int> dq;                          // indices with decreasing diff[]
        for (int i = 0; i < diffSize; ++i) {
            while (!dq.empty() && diff[dq.back()] <= diff[i]) dq.pop_back();
            dq.push_back(i);
            // keep only the last 'win' elements
            if (i - dq.front() >= win) dq.pop_front();

            int start = i - win + 1;            // window start index in diff[]
            if (start >= 0 && start <= limit) {
                good[start] = (diff[dq.front()] <= D);
            }
        }
    }

    long long cnt = 0;
    for (int i = 0; i <= limit && cnt < p; ) {
        if (good[i]) {
            ++cnt;
            i += k;
        } else {
            ++i;
        }
    }
    return cnt >= p;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    long long n, k, p;
    while (cin >> n >> k >> p) {
        vector<ll> h(n);
        for (int i = 0; i < n; ++i) cin >> h[i];
        sort(h.begin(), h.end());

        if (k == 1) {               // D is always 0
            cout << 0 << '\n';
            continue;
        }

        ll low = 0, high = h.back() - h.front();   // inclusive search space
        while (low < high) {
            ll mid = (low + high) / 2;
            if (can(h, (int)n, (int)k, (int)p, mid))
                high = mid;
            else
                low = mid + 1;
        }
        cout << low << '\n';
    }
    return 0;
}
