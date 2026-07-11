#include <iostream>
#include <vector>

using namespace std;

int main() {
    const int MAXP = 46341;
    vector<int> primes;
    vector<bool> is_prime(MAXP + 1, true);
    
    is_prime[0] = is_prime[1] = false;
    for (int i = 2; i <= MAXP; ++i) {
        if (is_prime[i]) {
            primes.push_back(i);
            for (int j = i * 2; j <= MAXP; j += i) {
                is_prime[j] = false;
            }
        }
    }
    
    long long n;
    while (cin >> n && n != 0) {
        cout << n << " = ";
        bool first = true;
        if (n < 0) {
            cout << "-1";
            n = -n;
            first = false;
        }
        if (n == 1) {
            if (first) cout << "1";
            else cout << " x 1";
        } else {
            for (int p : primes) {
                if ((long long)p * p > n) break;
                while (n % p == 0) {
                    if (!first) cout << " x ";
                    cout << p;
                    first = false;
                    n /= p;
                }
            }
            if (n > 1) {
                if (!first) cout << " x ";
                cout << n;
            }
        }
        cout << endl;
    }
    
    return 0;
}
