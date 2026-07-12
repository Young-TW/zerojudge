#include <iostream>
#include <string>
#include <algorithm>
#include <set>
using namespace std;

const int MAXN = 10000000;
bool isPrime[MAXN + 1];

void sieve() {
    fill(isPrime, isPrime + MAXN + 1, true);
    isPrime[0] = isPrime[1] = false;
    for (int i = 2; (long long)i * i <= MAXN; i++) {
        if (isPrime[i]) {
            for (int j = i * i; j <= MAXN; j += i) {
                isPrime[j] = false;
            }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    sieve();
    int c;
    cin >> c;
    while (c--) {
        string s;
        cin >> s;
        sort(s.begin(), s.end());
        set<int> primes;
        do {
            int num = 0;
            for (size_t i = 0; i < s.size(); i++) {
                num = num * 10 + (s[i] - '0');
                if (isPrime[num]) {
                    primes.insert(num);
                }
            }
        } while (next_permutation(s.begin(), s.end()));
        cout << primes.size() << "\n";
    }
    return 0;
}
