#include <bits/stdc++.h>
using namespace std;

struct PairHash {
    size_t operator()(const pair<long long,long long>& p) const noexcept {
        size_t h1 = std::hash<long long>{}(p.first);
        size_t h2 = std::hash<long long>{}(p.second);
        // simple combination
        return h1 ^ (h2 + 0x9e3779b9 + (h1<<6) + (h1>>2));
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    long long N;
    while ( (cin >> N) ) {
        vector<pair<long long,long long>> pts;
        pts.reserve(N);
        long long minY = LLONG_MAX, maxY = LLONG_MIN;
        for (long long i = 0; i < N; ++i) {
            long long x, y;
            cin >> x >> y;
            pts.emplace_back(x, y);
            if (y < minY) minY = y;
            if (y > maxY) maxY = y;
        }
        // single point or empty set is always symmetric
        if (N <= 1) {
            cout << "success\n";
            continue;
        }
        long long sumY = minY + maxY; // 2*c, may be odd
        unordered_set<pair<long long,long long>, PairHash> S;
        S.reserve(N * 2);
        for (auto &p : pts) S.insert(p);
        bool ok = true;
        for (auto &p : pts) {
            long long x = p.first;
            long long y = p.second;
            long long yMirror = sumY - y; // = 2c - y
            if (S.find({x, yMirror}) == S.end()) {
                ok = false;
                break;
            }
        }
        cout << (ok ? "success" : "failure") << '\n';
    }
    return 0;
}
