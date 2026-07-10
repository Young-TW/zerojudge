#include <iostream>
using namespace std;

int main() {
    int t;
    while (cin >> t) {
        while (t--) {
            long long n, c;
            cin >> n >> c;
            long long half = 1LL << (n - 1);
            long long ans = n * half;
            if (n % 2 == 1) ans += half;
            cout << ans * c << "\n";
        }
    }
    return 0;
}
