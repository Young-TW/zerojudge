#include <iostream>

using namespace std;

unsigned long long solve(unsigned long long x, unsigned long long n, unsigned long long m) {
    if (n == 0) return 1 % m;
    if (n % 2 == 1) {
        unsigned long long half = solve((x * x) % m, n / 2, m);
        return ((1 + x) * half) % m;
    } else {
        unsigned long long half = solve((x * x) % m, n / 2 - 1, m);
        return (1 + x * (1 + x) % m * half % m) % m;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    if (!(cin >> t)) return 0;
    while (t--) {
        unsigned long long x, n, m;
        if (!(cin >> x >> n >> m)) break;
        cout << solve(x, n, m) << "\n";
    }
    return 0;
}
