#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

long long euler_phi(long long n) {
    long long result = n;
    for (long long p = 2; p * p <= n; ++p) {
        if (n % p == 0) {
            while (n % p == 0)
                n /= p;
            result -= result / p;
        }
    }
    if (n > 1)
        result -= result / n;
    return result;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    long long n;
    while (cin >> n) {
        cout << euler_phi(n) << '\n';
    }
    return 0;
}
