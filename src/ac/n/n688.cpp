#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int N, K;
    while (cin >> N >> K) {
        vector<long long> a(N);
        long long S = 0;
        for (int i = 0; i < N; ++i) {
            cin >> a[i];
            S += a[i];
        }
        
        sort(a.begin(), a.end());
        
        vector<long long> P(N + 1, 0);
        for (int i = 0; i < N; ++i) {
            P[i + 1] = P[i] + a[i];
        }
        
        long long min_P = 1e18;
        int start_m = min(N, K);
        if (start_m % 2 != K % 2) {
            start_m--;
        }
        
        for (int m = start_m; m >= 0; m -= 2) {
            if (P[m] < min_P) {
                min_P = P[m];
            }
        }
        
        cout << S - 2 * min_P << "\n";
    }
    
    return 0;
}
