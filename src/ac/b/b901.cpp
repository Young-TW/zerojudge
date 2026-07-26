#include <iostream>

using namespace std;

int h(long long n) {
    int table[] = {1, 1, 1, 3, 3, 3, 3, 1, 1, 9};
    int res = 1;
    long long p = n / 10;
    int r = n % 10;
    if (p % 2 == 1) res = (res * 9) % 10;
    res = (res * table[r]) % 10;
    return res;
}

int F(long long n) {
    if (n == 0) return 1;
    return (h(n) * F(n / 2)) % 10;
}

int g(long long n) {
    if (n == 0) return 1;
    return (F(n) * g(n / 5)) % 10;
}

int power2(long long exp) {
    if (exp == 0) return 1;
    int table[] = {6, 2, 4, 8};
    return table[exp % 4];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    while (cin >> t) {
        while (t--) {
            long long n;
            cin >> n;
            long long c2 = 0, c5 = 0;
            for (long long i = 2; i <= n; i *= 2) c2 += n / i;
            for (long long i = 5; i <= n; i *= 5) c5 += n / i;
            long long diff = c2 - c5;
            int ans = (g(n) * power2(diff)) % 10;
            cout << ans << "\n";
        }
    }
    return 0;
}
