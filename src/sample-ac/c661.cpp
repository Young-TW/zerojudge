#include <iostream>

using namespace std;

long long S(long long x) {
    long long res = 0;
    for (long long p = 5; p <= x; p *= 5) {
        long long q = x / p;
        res += q * (x + 1) - p * q * (q + 1) / 2;
    }
    return res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int T;
    while (cin >> T) {
        while (T--) {
            long long n, m;
            cin >> n >> m;
            cout << S(m) - S(n - 1) << "\n";
        }
    }
    return 0;
}
