#include <iostream>
#include <vector>

using namespace std;

int sum_of_digits(long long n) {
    int sum = 0;
    while (n > 0) {
        sum += n % 10;
        n /= 10;
    }
    return sum;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    const int MAX_PRIME = 40000;
    vector<int> primes;
    vector<bool> is_comp(MAX_PRIME + 1, false);
    for (int i = 2; i <= MAX_PRIME; ++i) {
        if (!is_comp[i]) {
            primes.push_back(i);
            for (long long j = (long long)i * i; j <= MAX_PRIME; j += i) {
                is_comp[j] = true;
            }
        }
    }
    
    int T;
    if (cin >> T) {
        while (T--) {
            long long N;
            cin >> N;
            long long M = N + 1;
            while (true) {
                int sum_M = sum_of_digits(M);
                long long temp = M;
                int sum_prime = 0;
                bool is_prime = true;
                
                for (int p : primes) {
                    if ((long long)p * p > temp) break;
                    if (temp % p == 0) {
                        is_prime = false;
                        while (temp % p == 0) {
                            sum_prime += sum_of_digits(p);
                            temp /= p;
                        }
                    }
                }
                
                if (temp > 1) {
                    if (temp != M) {
                        sum_prime += sum_of_digits(temp);
                    } else {
                        is_prime = true;
                    }
                }
                
                if (!is_prime && sum_M == sum_prime) {
                    cout << M << "\n";
                    break;
                }
                M++;
            }
        }
    }
    return 0;
}
