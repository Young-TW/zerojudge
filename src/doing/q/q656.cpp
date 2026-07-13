#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    long long N, K;
    if (!(cin >> N >> K)) return 0;
    vector<long long> a;
    long long x;
    while (cin >> x) a.push_back(x);
    
    // 如果讀到的元素比 N 多，僅取前 N 個；若少於 N，視為已給完。
    if ((long long)a.size() > N) a.resize(N);
    
    long long n = a.size();
    long long total = 0;
    for (auto v : a) total += v;
    
    if (K == 1) {
        cout << total << "\n";
        return 0;
    }
    
    if (K > n) {
        long long posSum = 0;
        for (auto v : a) if (v > 0) posSum += v;
        cout << posSum << "\n";
        return 0;
    }
    
    long long cur = 0, best = LLONG_MIN;
    for (long long i = 0; i < n; ++i) {
        cur += a[i];
        if (i >= K) cur -= a[i - K];
        if (i >= K - 1) best = max(best, cur);
    }
    cout << best << "\n";
    return 0;
}
