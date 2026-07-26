#include <bits/stdc++.h>
using namespace std;

/* Fenwick Tree (Binary Indexed Tree) – 0‑based indices */
struct Fenwick {
    int n;
    vector<int> bit;
    Fenwick(int n = 0) { init(n); }
    void init(int n_) { n = n_; bit.assign(n + 1, 0); }
    // add val at position idx (0‑based)
    void add(int idx, int val) {
        for (int i = idx + 1; i <= n; i += i & -i) bit[i] += val;
    }
    // sum of positions [0 .. idx] (inclusive), idx may be -1 -> 0
    int sum(int idx) const {
        int s = 0;
        for (int i = idx + 1; i > 0; i -= i & -i) s += bit[i];
        return s;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int N;
    while (cin >> N) {
        vector<long long> a(N);
        for (int i = 0; i < N; ++i) cin >> a[i];

        if (N == 0) { cout << 0 << '\n'; continue; }

        int answer = (N == 1 ? 1 : 2);          // at least one (or two) elements

        // indices sorted by decreasing value
        vector<int> idx(N);
        iota(idx.begin(), idx.end(), 0);
        sort(idx.begin(), idx.end(),
             [&](int i, int j) { return a[i] > a[j]; });

        Fenwick bit(N);
        set<int> alive;
        for (int i = 0; i < N; ++i) alive.insert(i);

        for (int pos : idx) {
            // ----- try left end -----
            if (!alive.empty()) {
                auto itL = alive.begin();               // smallest alive index
                if (*itL < pos) {
                    int L = *itL;
                    int cnt = bit.sum(pos - 1) - bit.sum(L);
                    answer = max(answer, 2 + cnt);
                }
            }

            // ----- try right end -----
            if (!alive.empty()) {
                auto itR = alive.rbegin();              // largest alive index
                if (*itR > pos) {
                    int R = *itR;
                    int cnt = bit.sum(R) - bit.sum(pos);
                    answer = max(answer, 2 + cnt);
                }
            }

            // current position becomes a possible interior element
            bit.add(pos, 1);
            alive.erase(pos);
        }

        cout << answer << '\n';
    }
    return 0;
}
