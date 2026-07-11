#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int T;
    while (cin >> T) {
        while (T--) {
            int N;
            cin >> N;
            vector<long long> t(N + 1);
            for (int i = 1; i <= N; ++i) {
                cin >> t[i];
            }
            
            vector<long long> L(N + 1);
            L[1] = t[1];
            for (int i = 2; i <= N; ++i) {
                L[i] = max(L[i-1] + 1, t[i]);
            }
            
            vector<long long> R(N + 2);
            R[N] = t[N];
            for (int i = N - 1; i >= 1; --i) {
                R[i] = max(R[i+1] + 1, t[i]);
            }
            
            long long ans = 1e18;
            for (int k = 1; k <= N; ++k) {
                long long M = max(L[k], R[k]);
                long long time_T = max(2LL * N - k - 1, M);
                long long total = time_T + k - 1;
                if (total < ans) {
                    ans = total;
                }
            }
            cout << ans << "\n";
        }
    }
    return 0;
}
