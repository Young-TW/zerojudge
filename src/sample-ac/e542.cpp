#include <iostream>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    while (cin >> n) {
        if (n == 0) break;
        
        long long sum = 0;
        long long ans = 0;
        
        for (int i = 0; i < n; ++i) {
            int a;
            cin >> a;
            sum += a;
            if (sum > 0) {
                ans += sum;
            } else {
                ans -= sum;
            }
        }
        
        cout << ans << "\n";
    }
    
    return 0;
}
