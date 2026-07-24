#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int N;
    if (!(cin >> N)) return 0;
    vector<int> a(N);
    for (int i = 0; i < N; ++i) cin >> a[i];

    // count occurrences
    map<int, int, greater<int>> posCnt;   // positive (including 0), descending
    map<int, int, greater<int>> negCnt;   // negative, descending (e.g. -1, -2, ...)
    for (int v : a) {
        if (v >= 0) posCnt[v]++;          // treat 0 as positive
        else negCnt[v]++;                 // v is negative
    }

    vector<int> order;
    // 1. pair equal absolute values, positive first
    for (auto it = posCnt.begin(); it != posCnt.end(); ++it) {
        int v = it->first;
        while (it->second > 0) {
            auto nit = negCnt.find(-v);
            if (nit != negCnt.end() && nit->second > 0) {
                // output pair v, -v
                order.push_back(v);
                order.push_back(-v);
                --(it->second);
                --(nit->second);
                if (nit->second == 0) negCnt.erase(nit);
            } else break;
        }
    }

    // 2. remaining positives (still in descending order)
    for (auto &p : posCnt) {
        while (p.second-- > 0) order.push_back(p.first);
    }

    // 3. remaining negatives (descending, i.e. -1, -2, -3, ...)
    for (auto &p : negCnt) {
        while (p.second-- > 0) order.push_back(p.first);
    }

    // compute minimal required initial taste
    long long cur = 0;
    long long minPref = 0;
    for (int v : order) {
        cur += v;
        if (cur < minPref) minPref = cur;
    }
    long long need = (minPref < 0) ? -minPref : 0;

    cout << need << "\n";
    for (size_t i = 0; i < order.size(); ++i) {
        if (i) cout << ' ';
        cout << order[i];
    }
    cout << "\n";
    return 0;
}
