#include <iostream>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int k;
    while (cin >> k) {
        long double sum = 0.0L;
        long long n = 0;
        while (sum <= k) {
            ++n;
            sum += 1.0L / n;
        }
        cout << n << '\n';
    }
    
    return 0;
}
