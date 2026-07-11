#include <iostream>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    long long n;
    if (cin >> n) {
        int T = n;
        while (T-- && cin >> n) {
            if (n <= 0) {
                cout << 0 << "\n";
                continue;
            }
            long long res = 0;
            long long i = 1;
            while (i <= n) {
                long long q = n / i;
                long long next_i = n / q + 1;
                res += q * (next_i - i);
                i = next_i;
            }
            cout << res << "\n";
        }
    }
    return 0;
}
