#include <bits/stdc++.h>
using namespace std;

// 把 __int128 轉成十進位字串
string int128_to_string(__int128 x) {
    if (x == 0) return "0";
    bool neg = false;
    if (x < 0) {
        neg = true;
        x = -x;
    }
    string s;
    while (x > 0) {
        int digit = int(x % 10);
        s.push_back('0' + digit);
        x /= 10;
    }
    if (neg) s.push_back('-');
    reverse(s.begin(), s.end());
    return s;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    long long N, W;
    // ZeroJudge 可能有多筆測資，使用 while 讀到 EOF
    while (cin >> N >> W) {
        vector<pair<long long,long long>> a;
        a.reserve(N);
        for (long long i = 0; i < N; ++i) {
            long long c, v;
            cin >> c >> v;
            a.emplace_back(v, c); // 先存 (value, count) 方便排序
        }
        // 依價值降序
        sort(a.begin(), a.end(),
             [](const pair<long long,long long>& p1,
                const pair<long long,long long>& p2) {
                 return p1.first > p2.first;
             });
        
        long long remain = W;
        __int128 ans = 0;
        for (auto &p : a) {
            if (remain == 0) break;
            long long value = p.first;
            long long cnt   = p.second;
            long long take = (cnt < remain) ? cnt : remain;
            ans += (__int128)take * value;
            remain -= take;
        }
        cout << int128_to_string(ans) << '\n';
    }
    return 0;
}
