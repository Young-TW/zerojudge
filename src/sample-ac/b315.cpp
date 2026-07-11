#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    long long N, K;
    while (cin >> N >> K) {
        vector<long long> A(N);
        for (int i = 0; i < N; ++i) {
            cin >> A[i];
        }
        sort(A.begin(), A.end());
        
        long long L = 0, R = A[N - 1] - A[0];
        while (L < R) {
            long long M = L + (R - L + 1) / 2;
            long long cnt = 0;
            int ptr = 0;
            for (int j = 0; j < N; ++j) {
                while (ptr < N && A[ptr] <= A[j] - M) {
                    ptr++;
                }
                cnt += min(ptr, j);
            }
            if (cnt >= K) {
                L = M;
            } else {
                R = M - 1;
            }
        }
        cout << L << "\n";
    }
    
    return 0;
}
