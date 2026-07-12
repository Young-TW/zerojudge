#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    const int MAXP = 50000;
    vector<bool> is_composite(MAXP + 1, false);
    vector<int> primes;
    for (int i = 2; i <= MAXP; ++i) {
        if (!is_composite[i]) {
            primes.push_back(i);
            for (int j = i * 2; j <= MAXP; j += i) {
                is_composite[j] = true;
            }
        }
    }
    
    long long P;
    while (cin >> P) {
        long long ans = 1;
        long long temp = P;
        for (int p : primes) {
            if ((long long)p * p > temp) break;
            if (temp % p == 0) {
                long long sum = 1;
                long long term = 1;
                while (temp % p == 0) {
                    term *= p;
                    sum += term;
                    temp /= p;
                }
                ans *= sum;
            }
        }
        if (temp > 1) {
            ans *= (1 + temp);
        }
        cout << ans << "\n";
    }
    
    return 0;
}
