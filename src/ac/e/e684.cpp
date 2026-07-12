#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <cstring>
using namespace std;

const int MAX = 10000000;
vector<bool> is_prime(MAX + 1, true);
vector<int> anagrammatic_primes;

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

bool is_anagrammatic_prime(int n) {
    if (!is_prime[n]) return false;
    vector<int> digits;
    int temp = n;
    while (temp > 0) {
        digits.push_back(temp % 10);
        temp /= 10;
    }
    sort(digits.begin(), digits.end());
    do {
        int num = 0;
        for (int d : digits) {
            num = num * 10 + d;
        }
        if (!is_prime[num]) {
            return false;
        }
    } while (next_permutation(digits.begin(), digits.end()));
    return true;
}

void precompute_anagrammatic_primes() {
    for (int i = 2; i <= MAX; ++i) {
        if (is_anagrammatic_prime(i)) {
            anagrammatic_primes.push_back(i);
        }
    }
}

int find_next_anagrammatic_prime(int n) {
    int len = 0;
    int temp = n;
    while (temp > 0) {
        len++;
        temp /= 10;
    }
    int lower = 1;
    for (int i = 1; i < len; ++i) {
        lower *= 10;
    }
    int upper = lower * 10 - 1;

    auto it = upper_bound(anagrammatic_primes.begin(), anagrammatic_primes.end(), n);
    while (it != anagrammatic_primes.end()) {
        if (*it > upper) break;
        if (*it > n) return *it;
        ++it;
    }
    return 0;
}

int main() {
    sieve();
    precompute_anagrammatic_primes();
    int n;
    while (cin >> n && n != 0) {
        cout << find_next_anagrammatic_prime(n) << endl;
    }
    return 0;
}
