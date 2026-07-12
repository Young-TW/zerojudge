#include <iostream>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    while (cin >> n) {
        if (n == 0) break;
        
        long long ans = 0;
        int count[100] = {0};
        count[0] = 1;
        int sum = 0;
        
        for (int i = 0; i < n; ++i) {
            int p;
            cin >> p;
            sum = (sum + p) % 100;
            ans += count[sum];
            count[sum]++;
        }
        
        cout << ans << "\n";
    }
    
    return 0;
}
