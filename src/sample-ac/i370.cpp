#include <bits/stdc++.h>
using namespace std;

using uint32 = uint32_t;
using uint64 = uint64_t;
using uint16 = uint16_t;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    while (cin >> n >> m) {
        uint32 D11, S, A, O;
        cin >> D11 >> S >> A >> O;

        if (n < 2 || m < 2) {
            // still have to read the whole matrix generation to keep input sync
            // but we can skip storing it
            uint64 pre = D11;
            for (int i = 0; i < n; ++i) {
                for (int j = 0; j < m; ++j) {
                    if (i == 0 && j == 0) continue;
                    uint64 val = pre * (uint64)S;
                    val ^= (uint64)A;
                    val += (uint64)O;
                    val ^= 48763ULL;
                    val = (val * 1016ULL) % 1000000000ULL;
                    val += 1;
                    pre = val;
                }
            }
            cout << 0 << '\n';
            continue;
        }

        const size_t NM = (size_t)n * (size_t)m;
        vector<uint32> D(NM);
        D[0] = D11;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if (i == 0 && j == 0) continue;
                uint64 pre = (j > 0) ? D[(size_t)i * m + (j - 1)]
                                     : D[(size_t)(i - 1) * m + (m - 1)];
                uint64 val = pre * (uint64)S;
                val ^= (uint64)A;
                val += (uint64)O;
                val ^= 48763ULL;
                val = (val * 1016ULL) % 1000000000ULL;
                val += 1;
                D[(size_t)i * m + j] = (uint32)val;
            }
        }

        // auxiliary structures for the check routine
        const size_t MM = (size_t)m * (size_t)m;
        vector<uint16> seen(MM, 0);
        uint16 curStamp = 0;
        vector<int> cols; cols.reserve(m);

        auto check = [&](uint32 V) -> bool {
            ++curStamp;                     // new timestamp
            for (int i = 0; i < n; ++i) {
                cols.clear();
                size_t base = (size_t)i * m;
                for (int j = 0; j < m; ++j) {
                    if (D[base + j] >= V) cols.push_back(j);
                }
                int sz = (int)cols.size();
                if (sz < 2) continue;
                for (int a = 0; a < sz; ++a) {
                    int c1 = cols[a];
                    size_t off = (size_t)c1 * m;
                    for (int b = a + 1; b < sz; ++b) {
                        int c2 = cols[b];
                        size_t idx = off + c2;          // c1 < c2
                        if (seen[idx] == curStamp) return true;
                        seen[idx] = curStamp;
                    }
                }
            }
            return false;
        };

        uint32 lo = 1, hi = 1000000000U;
        while (lo < hi) {
            uint32 mid = lo + (hi - lo + 1) / 2;
            if (check(mid))
                lo = mid;
            else
                hi = mid - 1;
        }
        cout << lo << '\n';
    }
    return 0;
}
