#include <iostream>

using namespace std;

bool isPrime(unsigned long long n) {
    if (n <= 1) return false;
    if (n <= 3) return true;
    if (n % 2 == 0 || n % 3 == 0) return false;
    for (unsigned long long i = 5; i * i <= n; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0) return false;
    }
    return true;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int k;
    while (cin >> k && k != 0) {
        if (!isPrime(k)) {
            cout << "Given number is NOT prime! NO perfect number is available.\n";
        } else {
            unsigned long long m = (1ULL << k) - 1;
            if (isPrime(m)) {
                unsigned long long p = (1ULL << (k - 1)) * m;
                cout << "Perfect: " << p << "!\n";
            } else {
                cout << "Given number is prime. But, NO perfect number is available.\n";
            }
        }
    }
    
    return 0;
}
