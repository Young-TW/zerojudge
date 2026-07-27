#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    long long N, K;
    while (cin >> N >> K) {
        vector<long long> P(N);
        for (long long i = 0; i < N; ++i) cin >> P[i];

        unordered_map<long long, int> cnt;
        cnt.reserve(N * 2);
        cnt.max_load_factor(0.7);

        long long left = 0;
        long long distinct = 0;
        long long best = 0;

        for (long long right = 0; right < N; ++right) {
            if (++cnt[P[right]] == 1) ++distinct;

            while (distinct > K) {
                if (--cnt[P[left]] == 0) {
                    --distinct;
                    cnt.erase(P[left]);          // keep map small
                }
                ++left;
            }

            long long curLen = right - left + 1;
            if (curLen > best) best = curLen;
        }

        cout << best << '\n';
    }
    return 0;
}
