#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int N;
    long long M;
    while (cin >> N >> M) {
        vector<long long> A(N);
        for (int i = 0; i < N; ++i) {
            cin >> A[i];
        }
        
        if (M == 0) {
            cout << 0 << "\n";
            continue;
        }
        
        int left = 0;
        long long current_sum = 0;
        int ans = N + 1;
        
        for (int right = 0; right < N; ++right) {
            current_sum += A[right];
            while (current_sum >= M) {
                ans = min(ans, right - left + 1);
                current_sum -= A[left];
                ++left;
            }
        }
        
        if (ans == N + 1) {
            cout << "GGGGGZ\n";
        } else {
            cout << ans << "\n";
        }
    }
    
    return 0;
}
