#include <iostream>

using namespace std;

long long modpow(long long base, long long exp, long long modulus) {
    long long result = 1;
    base %= modulus;
    while (exp > 0) {
        if (exp & 1) {
            result = (result * base) % modulus;
        }
        base = (base * base) % modulus;
        exp >>= 1;
    }
    return result;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    long long M;
    while (cin >> M) {
        cout << modpow(3, M, 10007) << "\n";
    }
    return 0;
}
