#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

int main() {
    int Q;
    if (scanf("%d", &Q) != 1) return 0;
    
    vector<long long> A, pref, dp_prev, dp_cur;
    
    while (Q--) {
        int N;
        scanf("%d", &N);
        
        if ((int)A.size() < N) {
            A.resize(N);
            pref.resize(N + 1);
            dp_prev.resize(N);
            dp_cur.resize(N);
        }
        
        for (int i = 0; i < N; ++i) {
            scanf("%lld", &A[i]);
        }
        
        pref[0] = 0;
        for (int i = 0; i < N; ++i) {
            pref[i + 1] = pref[i] + A[i];
        }
        
        for (int i = 0; i < N; ++i) {
            dp_prev[i] = A[i];
        }
        
        for (int len = 2; len <= N; ++len) {
            for (int i = 0; i <= N - len; ++i) {
                int j = i + len - 1;
                long long S = pref[j + 1] - pref[i];
                dp_cur[i] = S - min(dp_prev[i + 1], dp_prev[i]);
            }
            swap(dp_prev, dp_cur);
        }
        
        printf("%lld\n", dp_prev[0]);
    }
    
    return 0;
}
