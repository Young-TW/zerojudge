#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    long long N;
    while (cin >> N) {
        vector<pair<long long,long long>> fac; // (p, c)
        fac.reserve(N);
        for (long long i = 0; i < N; ++i) {
            long long p, c;
            cin >> p >> c;
            fac.emplace_back(p, c);
        }
        long long M;
        cin >> M;

        // sort by productivity descending
        sort(fac.begin(), fac.end(),
             [](const pair<long long,long long>& a,
                const pair<long long,long long>& b) {
                 if (a.first != b.first) return a.first > b.first;
                 return a.second > b.second;
             });

        long long sum = 0;          // cumulative workers
        long long cntHigh = 0;      // factories with p > p*
        long long sumHigh = 0;      // workers taken from those factories
        long long pStar = -1;
        size_t idx = 0;

        // find first index where cumulative >= M
        for (size_t i = 0; i < fac.size(); ++i) {
            sum += fac[i].second;
            if (sum >= M) {
                idx = i;
                pStar = fac[i].first;
                break;
            }
        }

        // accumulate all factories with productivity > pStar
        for (size_t i = 0; i < fac.size(); ++i) {
            if (fac[i].first > pStar) {
                ++cntHigh;
                sumHigh += fac[i].second;
            } else break;
        }

        long long need = M - sumHigh;   // workers still required (0 <= need <= total of pStar group)

        // collect capacities of factories with productivity == pStar
        vector<long long> same;
        for (size_t i = 0; i < fac.size(); ++i) {
            if (fac[i].first == pStar) same.push_back(fac[i].second);
        }
        sort(same.begin(), same.end(), greater<long long>());

        long long cntSame = 0;
        long long acc = 0;
        for (long long c : same) {
            if (need <= 0) break;
            ++cntSame;
            acc += c;
            need -= c;
        }

        // if need <= 0 after taking some same‑productivity factories,
        // the answer is cntHigh + cntSame (cntSame may be 0 when need was 0)
        long long answer = cntHigh + (need <= 0 ? cntSame : 0);
        cout << answer << '\n';
    }
    return 0;
}
