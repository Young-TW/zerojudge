#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <cstring>
using namespace std;

const int MAX = 1000000;
vector<bool> is_prime(MAX + 1, true);
vector<int> circular_primes;

void sieve() {
    is_prime[0] = is_prime[1] = false;
    for (int i = 2; i * i <= MAX; ++i) {
        if (is_prime[i]) {
            for (int j = i * i; j <= MAX; j += i) {
                is_prime[j] = false;
            }
        }
    }
}

bool is_circular_prime(int n) {
    if (!is_prime[n]) return false;

    int digits = 0;
    int temp = n;
    while (temp > 0) {
        int d = temp % 10;
        if (d % 2 == 0 || d == 5) {
            return false;
        }
        temp /= 10;
        digits++;
    }

    int power = 1;
    for (int i = 1; i < digits; ++i) {
        power *= 10;
    }

    temp = n;
    for (int i = 0; i < digits - 1; ++i) {
        int first = temp / power;
        temp = (temp % power) * 10 + first;
        if (!is_prime[temp]) {
            return false;
        }
    }
    return true;
}

void precompute_circular_primes() {
    for (int i = 2; i < MAX; ++i) {
        if (is_circular_prime(i)) {
            circular_primes.push_back(i);
        }
    }
}

int main() {
    sieve();
    precompute_circular_primes();

    int i, j;
    while (cin >> i) {
        if (i == -1) break;
        cin >> j;

        auto lower = lower_bound(circular_primes.begin(), circular_primes.end(), i);
        auto upper = upper_bound(circular_primes.begin(), circular_primes.end(), j);
        int count = upper - lower;

        if (count == 0) {
            cout << "No Circular Primes." << endl;
        } else if (count == 1) {
            cout << "1 Circular Prime." << endl;
        } else {
            cout << count << " Circular Primes." << endl;
        }
    }

    return 0;
}
