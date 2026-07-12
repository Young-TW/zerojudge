#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    long long K;
    while (cin >> n >> K) {
        vector<long long> W(n), C(n);
        for (int i = 0; i < n; ++i) cin >> W[i];
        for (int i = 0; i < n; ++i) cin >> C[i];
        
        int n1 = n / 2;
        int n2 = n - n1;
        
        vector<pair<long long, long long>> A, B;
        
        for (int i = 0; i < (1 << n1); ++i) {
            long long w = 0, c = 0;
            for (int j = 0; j < n1; ++j) {
                if (i & (1 << j)) {
                    w += W[j];
                    c += C[j];
                }
            }
            if (w <= K) {
                A.push_back({w, c});
            }
        }
        
        for (int i = 0; i < (1 << n2); ++i) {
            long long w = 0, c = 0;
            for (int j = 0; j < n2; ++j) {
                if (i & (1 << j)) {
                    w += W[n1 + j];
                    c += C[n1 + j];
                }
            }
            if (w <= K) {
                B.push_back({w, c});
            }
        }
        
        sort(A.begin(), A.end());
        
        vector<pair<long long, long long>> filtered_A;
        long long max_c = -1;
        for (size_t i = 0; i < A.size(); ++i) {
            if (A[i].second > max_c) {
                filtered_A.push_back(A[i]);
                max_c = A[i].second;
            }
        }
        
        long long ans = 0;
        for (size_t i = 0; i < B.size(); ++i) {
            long long rem = K - B[i].first;
            if (rem < 0) continue;
            
            vector<pair<long long, long long>>::iterator it = upper_bound(filtered_A.begin(), filtered_A.end(), make_pair(rem, (long long)1e18));
            if (it != filtered_A.begin()) {
                --it;
                if (B[i].second + it->second > ans) {
                    ans = B[i].second + it->second;
                }
            } else {
                if (B[i].second > ans) {
                    ans = B[i].second;
                }
            }
        }
        
        cout << ans << "\n";
    }
    
    return 0;
}
