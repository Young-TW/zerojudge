#include <iostream>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    while (cin >> n) {
        if (n == 1) {
            cout << 0 << "\n";
            continue;
        }
        
        long long sum = 1; 
        for (int i = 2; i * i <= n; ++i) {
            if (n % i == 0) {
                sum += i;
                if (i != n / i) {
                    sum += n / i;
                }
            }
        }
        cout << sum << "\n";
    }
    
    return 0;
}
