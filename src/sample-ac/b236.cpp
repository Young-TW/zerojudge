#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    if (!(cin >> n)) return 0;
    
    if (n == 1) {
        cout << 1 << "\n";
        return 0;
    }
    
    const long long MOD = 1000000000;
    vector<long long> r(n);
    r[0] = 1;
    
    for (int i = 1; i < n; ++i) {
        long long sum = 0;
        int j = 0;
        int k = i - 1;
        for (; j < k; ++j, --k) {
            sum += 2 * r[j] * r[k];
            if (sum >= (1LL << 62)) {
                sum %= MOD;
            }
        }
        if (j == k) {
            sum += r[j] * r[j];
        }
        r[i] = (r[i - 1] + sum % MOD) % MOD;
    }
    
    cout << r[n - 1] << "\n";
    return 0;
}
