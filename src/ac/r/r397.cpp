#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdint>

using namespace std;

// ---------- Fenwick Tree (1‑based) ----------
class Fenwick {
    int n;
    vector<int> bit;          // frequencies, fit into int ( ≤ N )
public:
    explicit Fenwick(int n_ = 0) { init(n_); }
    void init(int n_) {
        n = n_;
        bit.assign(n + 1, 0);
    }
    // add delta at position p (1‑based)
    void add(int p, int delta) {
        for (int i = p; i <= n; i += i & -i) bit[i] += delta;
    }
    // sum of positions [1 .. p] (p may be 0)
    int sum(int p) const {
        int s = 0;
        for (int i = p; i > 0; i -= i & -i) s += bit[i];
        return s;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int N;
    while (cin >> N) {
        vector<pair<long long,long long>> singers(N);
        for (int i = 0; i < N; ++i) {
            long long a, b;
            cin >> a >> b;
            singers[i] = {a, b};
        }

        // sort by popularity Ai
        sort(singers.begin(), singers.end(),
             [](const pair<long long,long long>& p,
                const pair<long long,long long>& q){ return p.first < q.first; });

        vector<long long> A(N), B(N);
        for (int i = 0; i < N; ++i) {
            A[i] = singers[i].first;
            B[i] = singers[i].second;
        }

        // ----- build queries -----
        vector<vector<long long>> queries(N);          // thresholds stored per left index
        for (int i = 0; i < N; ++i) {
            long long needA = -A[i];
            int L = int(lower_bound(A.begin(), A.end(), needA) - A.begin());
            int left = max(i + 1, L);
            if (left < N) {
                queries[left].push_back(-B[i]);        // threshold = -Bi
            }
        }

        // ----- coordinate compression of B and -B -----
        vector<long long> coord;
        coord.reserve(2 * N);
        for (int i = 0; i < N; ++i) {
            coord.push_back(B[i]);
            coord.push_back(-B[i]);
        }
        sort(coord.begin(), coord.end());
        coord.erase(unique(coord.begin(), coord.end()), coord.end());

        auto getPos = [&](long long x) -> int {
            return int(lower_bound(coord.begin(), coord.end(), x) - coord.begin()) + 1; // 1‑based
        };

        Fenwick bit((int)coord.size());
        long long answer = 0;

        // ----- process from right to left -----
        for (int idx = N - 1; idx >= 0; --idx) {
            // insert current B[idx]
            bit.add(getPos(B[idx]), 1);

            // answer all queries that start at this idx
            for (long long thr : queries[idx]) {
                // number of values strictly smaller than thr
                int lessIdx = int(lower_bound(coord.begin(), coord.end(), thr) - coord.begin()); // 0‑based count
                int less = bit.sum(lessIdx);
                int total = bit.sum((int)coord.size());
                answer += (long long)(total - less);
            }
        }

        cout << answer << '\n';
    }
    return 0;
}
