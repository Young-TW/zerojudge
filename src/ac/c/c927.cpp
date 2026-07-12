#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int N;
    long long P;
    while (cin >> N >> P) {
        vector<long long> v1(N), v2(N), v3(N), v4(N);
        for (int i = 0; i < N; ++i) cin >> v1[i];
        for (int i = 0; i < N; ++i) cin >> v2[i];
        for (int i = 0; i < N; ++i) cin >> v3[i];
        for (int i = 0; i < N; ++i) cin >> v4[i];
        
        vector<long long> A;
        A.reserve((size_t)N * N);
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                A.push_back(v1[i] + v2[j]);
            }
        }
        
        sort(A.begin(), A.end());
        
        long long ans = 0;
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                long long target = P - (v3[i] + v4[j]);
                auto low = lower_bound(A.begin(), A.end(), target);
                auto high = upper_bound(A.begin(), A.end(), target);
                ans += (high - low);
            }
        }
        
        cout << ans << "\n";
    }
    
    return 0;
}
