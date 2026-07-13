#include <iostream>
#include <cstdint>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    long long n, m;
    while (cin >> n >> m) {
        if (n == 1) {
            cout << 1 % m << '\n';
            continue;
        }
        if (n == 2) {
            cout << 1 % m << '\n';
            continue;
        }
        uint64_t a_n2 = 1 % m; // a(1)
        uint64_t a_n1 = 1 % m; // a(2)
        uint64_t a_n = 0;
        for (long long i = 3; i <= n; ++i) {
            a_n = (uint64_t)(i - 1) * a_n1 + (uint64_t)(i - 2) * a_n2;
            a_n %= m;
            a_n2 = a_n1;
            a_n1 = a_n;
        }
        cout << a_n << '\n';
    }
    return 0;
}
