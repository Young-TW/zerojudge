#include <iostream>
#include <string>
#include <vector>

using namespace std;

vector<unsigned long long> primes;

void sieve() {
    int max_prime = 100000;
    vector<bool> is_comp(max_prime + 1, false);
    for (int i = 2; i <= max_prime; ++i) {
        if (!is_comp[i]) {
            primes.push_back(i);
            for (int j = i * 2; j <= max_prime; j += i) {
                is_comp[j] = true;
            }
        }
    }
}

bool is_prime(unsigned long long n) {
    if (n < 2) return false;
    for (size_t i = 0; i < primes.size(); ++i) {
        unsigned long long p = primes[i];
        if (p * p > n) break;
        if (n % p == 0) return false;
    }
    return true;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    sieve();
    
    string s;
    bool first_case = true;
    while (cin >> s) {
        if (!first_case) {
            cout << "\n";
        }
        first_case = false;
        
        vector<unsigned long long> found_primes;
        size_t i = 0;
        while (i < s.length()) {
            unsigned long long num = 0;
            bool found = false;
            for (size_t j = i; j < s.length(); ++j) {
                num = num * 10 + (s[j] - '0');
                if (is_prime(num)) {
                    found_primes.push_back(num);
                    i = j + 1;
                    found = true;
                    break;
                }
            }
            if (!found) {
                break;
            }
        }
        
        cout << found_primes.size() << "\n";
        for (size_t k = 0; k < found_primes.size(); ++k) {
            cout << found_primes[k] << "\n";
        }
    }
    
    return 0;
}
