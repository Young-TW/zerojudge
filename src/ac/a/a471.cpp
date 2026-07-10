#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
using namespace std;

int main() {
    long long n;
    while (cin >> n) {
        vector<pair<long long,long long>> ans;
        long long m = 2 * n;
        // k = number of terms, k>=2; s = a+b; s*k = 2n
        for (long long k = 2; k * k <= m; ++k) {
            if (m % k == 0) {
                long long s = m / k;
                // a,b integers <=> s,k opposite parity
                if (((s ^ k) & 1LL) && s >= k + 1) {
                    long long a = (s - k + 1) / 2;
                    long long b = (s + k - 1) / 2;
                    if (a > 0 && a < b) ans.push_back({a, b});
                }
                // paired divisor k' = m/k
                long long k2 = m / k;
                if (k2 != k && k2 >= 2) {
                    long long s2 = m / k2; // = k
                    if (((s2 ^ k2) & 1LL) && s2 >= k2 + 1) {
                        long long a = (s2 - k2 + 1) / 2;
                        long long b = (s2 + k2 - 1) / 2;
                        if (a > 0 && a < b) ans.push_back({a, b});
                    }
                }
            }
        }
        sort(ans.begin(), ans.end());
        if (ans.empty()) {
            cout << "No Solution...\n";
        } else {
            for (auto &p : ans) cout << p.first << "-" << p.second << "\n";
        }
        cout << "\n";
    }
    return 0;
}
