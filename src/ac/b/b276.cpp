#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    const long long NEG = -(1LL << 60);
    const int smallDist[8] = {4, 7, 8, 11, 12, 14, 15, 16};

    long long n, m;
    while (cin >> n >> m) {
        unordered_map<long long, long long> sum;   // coordinate -> total medicine
        sum.reserve(n * 2 + 10);
        for (long long i = 0; i < n; ++i) {
            long long a; int b;
            cin >> a >> b;
            sum[b] += a;
        }
        sum[0] = 0;                     // start cell

        // move to sorted vectors
        vector<pair<long long,long long>> vec;
        vec.reserve(sum.size());
        for (auto &p : sum) vec.emplace_back(p.first, p.second);
        sort(vec.begin(), vec.end(),
             [](const pair<long long,long long>& x,
                const pair<long long,long long>& y){ return x.first < y.first; });

        int K = (int)vec.size();
        vector<long long> pos(K), val(K);
        for (int i = 0; i < K; ++i) {
            pos[i] = vec[i].first;
            val[i] = vec[i].second;
        }

        unordered_map<long long,int> idx;
        idx.reserve(K * 2 + 10);
        for (int i = 0; i < K; ++i) idx[pos[i]] = i;

        vector<long long> dp(K, NEG), pref(K, NEG);
        dp[0] = 0;
        pref[0] = 0;
        long long answer = 0;

        for (int i = 1; i < K; ++i) {
            long long best = NEG;

            // distance >= 18  -> use prefix maximum
            if (pos[i] >= 18) {
                long long target = pos[i] - 18;
                int j = (int)(upper_bound(pos.begin(), pos.begin() + i, target) - pos.begin()) - 1;
                if (j >= 0) best = max(best, pref[j]);
            }

            // distances in the small set
            for (int d : smallDist) {
                long long need = pos[i] - d;
                if (need < 0) continue;
                auto it = idx.find(need);
                if (it != idx.end()) {
                    int j = it->second;
                    best = max(best, dp[j]);
                }
            }

            if (best != NEG) dp[i] = val[i] + best;
            // else dp[i] stays NEG (unreachable)

            pref[i] = max(pref[i-1], dp[i]);
            answer = max(answer, dp[i]);
        }

        cout << answer << '\n';
    }
    return 0;
}
