#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    while (cin >> n) {
        long long l, r;
        cin >> l >> r;
        vector<long long> a(n);
        for (int i = 0; i < n; ++i) {
            cin >> a[i];
        }
        
        int n1 = n / 2;
        int n2 = n - n1;
        
        vector<long long> S1, S2;
        
        for (int mask = 0; mask < (1 << n1); ++mask) {
            long long sum = 0;
            for (int i = 0; i < n1; ++i) {
                if (mask & (1 << i)) {
                    sum += a[i];
                }
            }
            S1.push_back(sum);
        }
        
        for (int mask = 0; mask < (1 << n2); ++mask) {
            long long sum = 0;
            for (int i = 0; i < n2; ++i) {
                if (mask & (1 << i)) {
                    sum += a[n1 + i];
                }
            }
            S2.push_back(sum);
        }
        
        sort(S2.begin(), S2.end());
        
        long long ans = 0;
        for (long long x : S1) {
            long long low = l - x;
            long long high = r - x;
            auto it1 = lower_bound(S2.begin(), S2.end(), low);
            auto it2 = upper_bound(S2.begin(), S2.end(), high);
            ans += (it2 - it1);
        }
        
        cout << ans << "\n";
    }
    
    return 0;
}
