#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdint>

struct Wave {
    char dir;
    long long d;
    long long v;
    int idx;               // original position, used only for stability
};

int priority(char c) {
    // W < S < E < N
    switch (c) {
        case 'W': return 0;
        case 'S': return 1;
        case 'E': return 2;
        case 'N': return 3;
    }
    return 4; // never reached
}

bool cmp(const Wave& a, const Wave& b) {
    __int128 left  = (__int128)a.d * b.v;
    __int128 right = (__int128)b.d * a.v;
    if (left != right) return left < right;               // earlier arrival
    int pa = priority(a.dir);
    int pb = priority(b.dir);
    if (pa != pb) return pa < pb;                         // same time, priority
    return false;                                         // equal, keep stability
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int P;
    while (std::cin >> P) {
        std::vector<Wave> waves;
        waves.reserve(P);
        for (int i = 0; i < P; ++i) {
            Wave w;
            std::cin >> w.dir >> w.d >> w.v;
            w.idx = i;
            waves.push_back(w);
        }
        std::stable_sort(waves.begin(), waves.end(), cmp);
        for (const auto& w : waves) std::cout << w.dir;
        std::cout << '\n';
    }
    return 0;
}
