#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    long long N, C;
    while (cin >> N >> C) {
        vector<long long> a(N);
        for (int i = 0; i < N; ++i) {
            cin >> a[i];
        }
        sort(a.begin(), a.end());
        
        auto check = [&](long long U) -> bool {
            long long sum = 0;
            for (int i = 0; i < N; ++i) {
                if (a[i] >= U) break;
                long long diff = U - a[i];
                sum += diff * diff;
                if (sum > C) return false;
            }
            return true;
        };
        
        long long L = a[0];
        long long R = 30000005;
        long long ans = L;
        while (L <= R) {
            long long mid = L + (R - L) / 2;
            if (check(mid)) {
                ans = mid;
                L = mid + 1;
            } else {
                R = mid - 1;
            }
        }
        cout << ans << "\n";
    }
    return 0;
}
