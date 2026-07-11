#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, k;
    while (cin >> n >> k) {
        vector<long long> a(n);
        for (int i = 0; i < n; i++) cin >> a[i];
        sort(a.begin(), a.end());
        
        vector<long long> S(n + 1, 0);
        for (int i = 0; i < n; i++) S[i + 1] = S[i] + a[i];
        
        auto cost = [&](int l) -> long long {
            int r = l + k - 1;
            int m = l + (k - 1) / 2;
            long long left = a[m] * (long long)(m - l + 1) - (S[m + 1] - S[l]);
            long long right = (S[r + 1] - S[m]) - a[m] * (long long)(r - m + 1);
            return left + right;
        };
        
        int numIntervals = n - k + 1;
        vector<long long> prefMin(numIntervals);
        prefMin[0] = cost(0);
        for (int i = 1; i < numIntervals; i++) {
            prefMin[i] = min(prefMin[i - 1], cost(i));
        }
        
        long long ans = LLONG_MAX;
        for (int l2 = k; l2 <= n - k; l2++) {
            long long c2 = cost(l2);
            long long c1 = prefMin[l2 - k];
            ans = min(ans, c1 + c2);
        }
        
        cout << ans << "\n";
    }
    return 0;
}
