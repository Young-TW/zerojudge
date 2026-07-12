#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include <functional>
#include <numeric>
#include <cstring>

using namespace std;

long long exgcd(long long a, long long b, long long &x, long long &y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    long long d = exgcd(b, a % b, y, x);
    y -= (a / b) * x;
    return d;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    long long M;
    while (cin >> M) {
        vector<long long> factors;
        for (long long i = 1; i * i <= M; ++i) {
            if (M % i == 0) {
                factors.push_back(i);
                if (i * i != M) {
                    factors.push_back(M / i);
                }
            }
        }
        set<long long> ans_set;
        for (long long d1 : factors) {
            long long d2 = M / d1;
            long long p, q;
            long long g = exgcd(d1, d2, p, q);
            if ((d2 - 2) % g != 0) continue;
            long long m2_div_g = d2 / g;
            long long k = ((p % m2_div_g) + m2_div_g) % m2_div_g;
            k = (k * (((d2 - 2) / g) % m2_div_g)) % m2_div_g;
            long long lcm = d1 / g * d2;
            long long x0 = 1 + d1 * k;
            x0 = (x0 % lcm + lcm) % lcm;
            if (x0 == 0) x0 = lcm;
            for (long long cur = x0; cur <= M; cur += lcm) {
                ans_set.insert(cur);
            }
        }
        cout << ans_set.size() << "\n";
        for (long long x : ans_set) {
            cout << x << "\n";
        }
    }
    return 0;
}
