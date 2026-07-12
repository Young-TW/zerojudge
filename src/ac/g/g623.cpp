#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int T;
    if (!(cin >> T)) return 0;
    
    while (T--) {
        int N;
        cin >> N;
        vector<int> A(N);
        for (int i = 0; i < N; ++i) {
            cin >> A[i];
        }
        sort(A.begin(), A.end());
        
        long long total_comb = 1LL * N * (N - 1) * (N - 2) / 6;
        long long bad_comb = 0;
        
        for (int i = 0; i < N; ) {
            int j = i;
            while (j < N && A[j] == A[i]) {
                ++j;
            }
            long long c = j - i;
            if (c >= 2) {
                long long c2 = c * (c - 1) / 2;
                bad_comb += c2 * (N - c);
            }
            if (c >= 3) {
                long long c3 = c * (c - 1) * (c - 2) / 6;
                bad_comb += c3;
            }
            i = j;
        }
        
        cout << total_comb - bad_comb << "\n";
    }
    
    return 0;
}
