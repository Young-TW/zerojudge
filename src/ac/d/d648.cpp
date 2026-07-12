#include <iostream>

using namespace std;

long long gcd(long long a, long long b) {
    long long temp;
    while (b) {
        temp = a % b;
        a = b;
        b = temp;
    }
    return a;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    long long n, m;
    while (cin >> n >> m) {
        if (n == 0 && m == 0) break;
        if (gcd(n, m) == 1 && (n % 2 != m % 2)) {
            cout << "YES\n";
        } else {
            cout << "Impossible\n";
        }
    }
    return 0;
}
