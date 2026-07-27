#include <bits/stdc++.h>
using namespace std;

using int64 = long long;
using u128 = unsigned __int128;

/* convert unsigned __int128 to decimal string */
string toString(u128 x) {
    if (x == 0) return "0";
    string s;
    while (x > 0) {
        int digit = x % 10;
        s.push_back('0' + digit);
        x /= 10;
    }
    reverse(s.begin(), s.end());
    return s;
}

/* factorials up to 31! (fits into unsigned __int128) */
u128 fact[32];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    fact[0] = 1;
    for (int i = 1; i <= 31; ++i) fact[i] = fact[i - 1] * (u128)i;

    int64 n;
    while (cin >> n) {
        // factorisation
        vector<int64> primes;
        int64 tmp = n;
        while ((tmp & 1LL) == 0) {
            primes.push_back(2);
            tmp >>= 1;
        }
        for (int64 p = 3; p * p <= tmp; p += 2) {
            while (tmp % p == 0) {
                primes.push_back(p);
                tmp /= p;
            }
        }
        if (tmp > 1) primes.push_back(tmp);

        // minimal key presses
        int64 minPress = 0;
        for (int64 p : primes) minPress += p;

        // count multiplicities
        map<int64, int> cnt;
        for (int64 p : primes) ++cnt[p];

        int t = 0;                     // number of factor 2
        if (cnt.count(2)) {
            t = cnt[2];
            cnt.erase(2);
        }

        // store other counts in a vector
        vector<int> otherCnt;
        for (auto &kv : cnt) otherCnt.push_back(kv.second);
        int otherTotal = 0;
        for (int c : otherCnt) otherTotal += c;

        u128 totalWays = 0;

        for (int a = 0; a <= t / 2; ++a) {
            int cnt2 = t - 2 * a;
            int cnt4 = a;
            int totalBlocks = cnt2 + cnt4 + otherTotal;

            u128 ways = fact[totalBlocks];
            // divide by factorials of each multiplicity
            if (cnt2 > 0) ways /= fact[cnt2];
            if (cnt4 > 0) ways /= fact[cnt4];
            for (int c : otherCnt) if (c > 0) ways /= fact[c];

            totalWays += ways;
        }

        cout << "min : " << minPress << "\n";
        cout << "way : " << toString(totalWays) << "\n";
    }
    return 0;
}
