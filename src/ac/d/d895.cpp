#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <cstdint>
#include <utility>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);

    int N, M;
    while (std::cin >> N >> M) {
        const int NM = N * M;
        std::vector<int> h(NM);
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < M; ++j) {
                std::cin >> h[i * M + j];
            }
        }

        const int W = (M + 63) / 64;
        std::vector<std::uint64_t> reach((size_t)NM * W, 0ULL);

        auto set_bit = [&](int idx, int col) {
            reach[(size_t)idx * W + (col >> 6)] |= (1ULL << (col & 63));
        };
        auto get_bit = [&](int idx, int col) -> bool {
            return (reach[(size_t)idx * W + (col >> 6)] >> (col & 63)) & 1ULL;
        };

        for (int j = 0; j < M; ++j) {
            set_bit((N - 1) * M + j, j);
        }

        std::vector<int> order(NM);
        std::iota(order.begin(), order.end(), 0);
        std::sort(order.begin(), order.end(), [&](int a, int b) {
            return h[a] < h[b];
        });

        const int di[4] = {0, 0, 1, -1};
        const int dj[4] = {1, -1, 0, 0};

        for (int idx : order) {
            int i = idx / M, j = idx % M;
            size_t base = (size_t)idx * W;
            for (int d = 0; d < 4; ++d) {
                int ni = i + di[d], nj = j + dj[d];
                if (ni < 0 || ni >= N || nj < 0 || nj >= M) continue;
                int nidx = ni * M + nj;
                if (h[nidx] < h[idx]) {
                    size_t nbase = (size_t)nidx * W;
                    for (int w = 0; w < W; ++w) {
                        reach[base + w] |= reach[nbase + w];
                    }
                }
            }
        }

        std::vector<std::uint64_t> all(W, 0ULL);
        for (int j = 0; j < M; ++j) {
            size_t base = (size_t)j * W;
            for (int w = 0; w < W; ++w) all[w] |= reach[base + w];
        }

        int missing = 0;
        for (int j = 0; j < M; ++j) {
            if (!((all[j >> 6] >> (j & 63)) & 1ULL)) ++missing;
        }

        if (missing > 0) {
            std::cout << 0 << '\n' << missing << '\n';
            continue;
        }

        std::vector<std::pair<int, int> > intervals;
        intervals.reserve(M);
        for (int j = 0; j < M; ++j) {
            int l = M, r = -1;
            for (int col = 0; col < M; ++col) {
                if (get_bit(j, col)) {
                    if (col < l) l = col;
                    if (col > r) r = col;
                }
            }
            if (l <= r) intervals.push_back(std::make_pair(l, r));
        }

        std::sort(intervals.begin(), intervals.end());
        int cur = 0, ans = 0, p = 0;
        while (cur < M) {
            int best = -1;
            while (p < (int)intervals.size() && intervals[p].first <= cur) {
                if (intervals[p].second > best) best = intervals[p].second;
                ++p;
            }
            if (best < cur) break;
            cur = best + 1;
            ++ans;
        }

        std::cout << 1 << '\n' << ans << '\n';
    }
    return 0;
}
