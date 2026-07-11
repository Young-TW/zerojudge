#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    while (cin >> n) {
        vector<bool> is_prime(n + 1, true);
        vector<int> primes;
        
        for (int i = 2; i <= n; ++i) {
            if (is_prime[i]) {
                primes.push_back(i);
                for (int j = i * 2; j <= n; j += i) {
                    is_prime[j] = false;
                }
            }
        }
        
        cout << n << "!=";
        for (size_t i = 0; i < primes.size(); ++i) {
            int p = primes[i];
            int exp = 0;
            long long power = p;
            while (power <= n) {
                exp += n / power;
                power *= p;
            }
            if (i > 0) cout << " ";
            cout << exp;
        }
        cout << "\n";
    }
    
    return 0;
}
