#include <iostream>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    long long n, k;
    while (cin >> n >> k) {
        long long ans = n;
        long long butts = n;
        while (butts >= k) {
            long long new_cigs = butts / k;
            ans += new_cigs;
            butts = butts % k + new_cigs;
        }
        cout << ans << "\n";
    }
    
    return 0;
}
