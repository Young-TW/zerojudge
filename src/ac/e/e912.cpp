#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    const int MAXN = 10000;
    vector<bool> is_composite(MAXN + 1, false);
    vector<int> primes;
    
    for (int i = 2; i <= MAXN; ++i) {
        if (!is_composite[i]) {
            primes.push_back(i);
            for (long long j = (long long)i * i; j <= MAXN; j += i) {
                is_composite[j] = true;
            }
        }
    }

    int n;
    while (cin >> n) {
        cout << n << "! = ";
        bool first = true;
        for (int p : primes) {
            if (p > n) break;
            int exp = 0;
            long long power = p;
            while (power <= n) {
                exp += n / power;
                power *= p;
            }
            if (!first) {
                cout << " * ";
            }
            first = false;
            cout << p << "^" << exp;
        }
        cout << "\n";
    }

    return 0;
}
