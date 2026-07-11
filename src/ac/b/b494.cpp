#include <cstdio>
#include <cstdint>
#include <algorithm>
#include <vector>
#include <utility>

uint32_t seed;

inline uint32_t p_random() {
    return seed = seed * 9301u + 49297u;
}

int main() {
    int N, M;
    uint32_t S;
    if (scanf("%d %d %u", &N, &M, &S) != 3) return 0;
    seed = S;

    std::vector<uint32_t> tree(2 * N);
    for (int i = 0; i < N; ++i) {
        tree[N + i] = p_random();
    }
    for (int i = N - 1; i > 0; --i) {
        tree[i] = std::max(tree[i << 1], tree[i << 1 | 1]);
    }

    uint32_t hash = 0;
    for (int i = 0; i < M; ++i) {
        int x = p_random() % N + 1;
        int y = p_random() % N + 1;
        if (x > y) std::swap(x, y);
        int l = x - 1;
        int r = y;
        uint32_t max_val = 0;
        for (l += N, r += N; l < r; l >>= 1, r >>= 1) {
            if (l & 1) max_val = std::max(max_val, tree[l++]);
            if (r & 1) max_val = std::max(max_val, tree[--r]);
        }
        hash ^= max_val;
    }

    printf("%u\n", hash);
    return 0;
}
