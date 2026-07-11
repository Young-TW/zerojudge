#include <iostream>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    long long n;
    while (cin >> n) {
        long long sum = 0;
        if (n > 1) {
            sum = 1;
            for (long long i = 2; i * i <= n; ++i) {
                if (n % i == 0) {
                    sum += i;
                    if (i * i != n) {
                        sum += n / i;
                    }
                }
            }
        }
        
        cout << sum << "\n";
        if (sum == n) {
            cout << "perfect\n";
        } else {
            cout << "not perfect\n";
        }
    }
    return 0;
}
