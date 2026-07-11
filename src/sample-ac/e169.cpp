#include <iostream>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    while (cin >> n && n) {
        long long cnt[100] = {0};
        long long ans = 0;
        for (int i = 0; i < n; ++i) {
            long long p;
            cin >> p;
            int r = p % 100;
            int target = (100 - r) % 100;
            ans += cnt[target];
            cnt[r]++;
        }
        cout << ans << "\n";
    }
    
    return 0;
}
