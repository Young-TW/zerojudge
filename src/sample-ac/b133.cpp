#include <iostream>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int k, N;
    while (cin >> k >> N) {
        long long ans = 0;
        long long power = 1;
        while (N > 0) {
            if (N & 1) {
                ans += power;
            }
            power *= k;
            N >>= 1;
        }
        cout << ans << "\n";
    }
    
    return 0;
}
