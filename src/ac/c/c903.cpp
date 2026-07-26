#include <iostream>
#include <cstdio>
#include <utility>
using namespace std;

const int MOD = 1000;

pair<int,int> calc(int n) {
    if (n == 0) return make_pair(2, 4);
    pair<int,int> p = calc(n >> 1);
    int ak = p.first, ak1 = p.second;
    long long a2k = (1LL * ak * ak - 2) % MOD;
    if (a2k < 0) a2k += MOD;
    long long a2k1 = (1LL * ak * ak1 - 4) % MOD;
    if (a2k1 < 0) a2k1 += MOD;
    if (n & 1) {
        long long a2k2 = (1LL * ak1 * ak1 - 2) % MOD;
        if (a2k2 < 0) a2k2 += MOD;
        return make_pair((int)a2k1, (int)a2k2);
    } else {
        return make_pair((int)a2k, (int)a2k1);
    }
}

int main() {
    int n;
    while (cin >> n) {
        int an = calc(n).first;
        int ans = (an - 1) % MOD;
        if (ans < 0) ans += MOD;
        printf("%03d\n", ans);
    }
    return 0;
}
