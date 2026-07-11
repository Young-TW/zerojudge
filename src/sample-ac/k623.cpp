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
            int n;
            cin >> n;
            vector<int> c(n + 1, 0);
            for (int i = 0; i < n; ++i) {
                int p;
                cin >> p;
                c[p]++;
            }
            
            vector<long long> S(n);
            long long sum = 0;
            for (int i = 0; i < n; ++i) {
                sum += c[i + 1] - 1;
                S[i] = sum;
            }
            
            sort(S.begin(), S.end());
            long long median = S[n / 2];
            
            long long ans = 0;
            for (int i = 0; i < n; ++i) {
                long long diff = S[i] - median;
                ans += diff < 0 ? -diff : diff;
            }
            
            cout << ans << "\n";
        }
    }
    
    return 0;
}
