#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int N;
    long long T;
    while (cin >> N >> T) {
        vector<long long> s(N);
        for (int i = 0; i < N; ++i) {
            cin >> s[i];
        }
        
        int mid = N / 2;
        vector<long long> A;
        A.reserve(1 << mid);
        A.push_back(0);
        for (int i = 0; i < mid; ++i) {
            int sz = A.size();
            for (int j = 0; j < sz; ++j) {
                A.push_back(A[j] + s[i]);
            }
        }
        
        vector<long long> B;
        int rem = N - mid;
        B.reserve(1 << rem);
        B.push_back(0);
        for (int i = mid; i < N; ++i) {
            int sz = B.size();
            for (int j = 0; j < sz; ++j) {
                B.push_back(B[j] + s[i]);
            }
        }
        
        sort(A.begin(), A.end());
        
        long long ans = 0;
        for (long long b : B) {
            long long target = T - b;
            auto low = lower_bound(A.begin(), A.end(), target);
            auto high = upper_bound(A.begin(), A.end(), target);
            ans += (high - low);
        }
        
        if (T == 0) {
            ans--;
        }
        
        cout << ans << "\n";
    }
    
    return 0;
}
