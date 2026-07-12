#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int N, M;
    while (cin >> N >> M) {
        vector<long long> F(N);
        vector<long long> G(N);
        
        for (int i = 0; i < N; ++i) {
            F[i] = (long long)i * i + (N - 10000LL) * i;
            G[i] = (long long)i * i + i;
        }
        
        sort(F.begin(), F.end());
        
        long long low = F[0] + G[0];
        long long high = F[N - 1] + G[N - 1];
        
        while (low < high) {
            long long mid = low + (high - low) / 2;
            long long cnt = 0;
            int j = N - 1;
            
            for (int i = 0; i < N; ++i) {
                while (j >= 0 && F[i] + G[j] > mid) {
                    --j;
                }
                if (j < 0) break;
                cnt += (j + 1);
            }
            
            if (cnt >= M) {
                high = mid;
            } else {
                low = mid + 1;
            }
        }
        
        cout << low << "\n";
    }
    
    return 0;
}
