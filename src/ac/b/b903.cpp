#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Pair {
    int a, b;
    long long e;
    bool operator<(const Pair& other) const {
        if (a != other.a) return a < other.a;
        return b > other.b;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int N, M, K;
    while (cin >> N >> M >> K) {
        vector<Pair> pairs(K);
        for (int i = 0; i < K; ++i) {
            cin >> pairs[i].a >> pairs[i].b >> pairs[i].e;
        }
        sort(pairs.begin(), pairs.end());
        vector<long long> tree(M + 1, 0);
        long long ans = 0;
        for (int i = 0; i < K; ++i) {
            int b = pairs[i].b;
            long long max_val = 0;
            for (int j = b - 1; j > 0; j -= j & (-j)) {
                if (tree[j] > max_val) max_val = tree[j];
            }
            long long val = max_val + pairs[i].e;
            for (int j = b; j <= M; j += j & (-j)) {
                if (val > tree[j]) tree[j] = val;
            }
            if (val > ans) ans = val;
        }
        cout << ans << "\n";
    }
    return 0;
}
