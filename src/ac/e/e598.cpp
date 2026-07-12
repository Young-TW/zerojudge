#include <iostream>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    long long n;
    while (cin >> n) {
        bool outstanding = true;
        for (int k = 2; k <= 9; ++k) {
            if (n % k == 0 && n / k >= 100000000) {
                outstanding = false;
                break;
            }
        }
        cout << (outstanding ? "yes" : "no") << "\n";
    }
    
    return 0;
}
