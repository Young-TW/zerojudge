#include <iostream>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    long long x0, y0;
    while (cin >> x0 >> y0) {
        if (y0 % x0 != 0) {
            cout << 0 << "\n";
            continue;
        }
        
        long long k = y0 / x0;
        int distinct_prime_factors = 0;
        
        for (long long i = 2; i * i <= k; ++i) {
            if (k % i == 0) {
                distinct_prime_factors++;
                while (k % i == 0) {
                    k /= i;
                }
            }
        }
        
        if (k > 1) {
            distinct_prime_factors++;
        }
        
        cout << (1LL << distinct_prime_factors) << "\n";
    }
    
    return 0;
}
