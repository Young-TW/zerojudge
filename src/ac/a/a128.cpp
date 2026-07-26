#include <bits/stdc++.h>
using namespace std;

int X, Y;
vector<int> a;                     // areas > 0
int M;                             // number of friends after removing zeros
vector<int> sumMask;               // sum[mask]
vector< unordered_map<int, char> > memo;   // 0 = unknown, 1 = true, 2 = false

bool dfs(int mask, int w) {
    auto it = memo[mask].find(w);
    if (it != memo[mask].end()) return it->second == 1;

    int area = sumMask[mask];
    if (area % w != 0) {
        memo[mask][w] = 2;
        return false;
    }
    int h = area / w;

    // only one friend -> always possible
    if ((mask & (mask - 1)) == 0) {
        memo[mask][w] = 1;
        return true;
    }

    // iterate over proper non‑empty sub‑masks
    for (int sub = (mask - 1) & mask; sub; sub = (sub - 1) & mask) {
        int other = mask ^ sub;
        int subArea = sumMask[sub];

        // vertical cut (parallel to height)
        if (subArea % h == 0) {
            int w1 = subArea / h;
            if (w1 > 0 && w1 < w) {
                if (dfs(sub, w1) && dfs(other, w - w1)) {
                    memo[mask][w] = 1;
                    return true;
                }
            }
        }

        // horizontal cut (parallel to width)
        if (subArea % w == 0) {
            int h1 = subArea / w;
            if (h1 > 0 && h1 < h) {
                if (dfs(sub, w) && dfs(other, w)) {
                    memo[mask][w] = 1;
                    return true;
                }
            }
        }
    }

    memo[mask][w] = 2;
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, caseNo = 0;
    while (cin >> n) {
        if (n == 0) break;
        ++caseNo;
        cin >> X >> Y;
        a.clear();
        for (int i = 0; i < n; ++i) {
            int v; cin >> v;
            if (v > 0) a.push_back(v);          // ignore zero requests
        }
        M = (int)a.size();

        long long total = 0;
        for (int v : a) total += v;
        if (total != 1LL * X * Y) {
            cout << "Case " << caseNo << ": No\n";
            continue;
        }

        int FULL = (1 << M) - 1;
        sumMask.assign(1 << M, 0);
        for (int mask = 1; mask <= FULL; ++mask) {
            int low = mask & -mask;
            int idx = __builtin_ctz(low);
            sumMask[mask] = sumMask[mask ^ low] + a[idx];
        }

        memo.assign(1 << M, unordered_map<int, char>());

        bool ok = dfs(FULL, X) || dfs(FULL, Y);
        cout << "Case " << caseNo << ": " << (ok ? "Yes" : "No") << "\n";
    }
    return 0;
}
