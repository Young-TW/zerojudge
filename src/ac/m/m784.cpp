#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int N, M;
    while (cin >> N >> M) {
        vector<int> A(N);
        int max_A = 0;
        long long sum_A = 0;
        for (int i = 0; i < N; ++i) {
            cin >> A[i];
            if (A[i] > max_A) {
                max_A = A[i];
            }
            sum_A += A[i];
        }
        
        long long L = max_A;
        long long R = sum_A;
        
        while (L < R) {
            long long mid = L + (R - L) / 2;
            int groups = 1;
            long long current_sum = 0;
            
            for (int i = 0; i < N; ++i) {
                if (current_sum + A[i] > mid) {
                    groups++;
                    current_sum = A[i];
                } else {
                    current_sum += A[i];
                }
            }
            
            if (groups <= M) {
                R = mid;
            } else {
                L = mid + 1;
            }
        }
        
        cout << L << "\n";
    }
    
    return 0;
}
