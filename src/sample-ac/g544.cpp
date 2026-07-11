#include <iostream>
#include <vector>
#include <cstdio>
#include <algorithm>

using namespace std;

const long long NEG_INF = -1e18;

inline bool readInt(int &x) {
    x = 0;
    char c = getchar();
    while (c != EOF && (c < '0' || c > '9')) {
        c = getchar();
    }
    if (c == EOF) return false;
    while (c >= '0' && c <= '9') {
        x = x * 10 + (c - '0');
        c = getchar();
    }
    return true;
}

int main() {
    int N, K;
    while (readInt(N)) {
        if (!readInt(K)) break;
        vector<int> S(N);
        vector<int> W(N);
        for (int i = 0; i < N; ++i) {
            readInt(S[i]);
        }
        for (int i = 0; i < N; ++i) {
            readInt(W[i]);
        }
        
        vector<long long> dp(K + 1, NEG_INF);
        dp[0] = 0;
        
        long long mx1 = 0;
        int idx1 = 0;
        long long mx2 = NEG_INF;
        int idx2 = 1; // 只要不等於 0 即可
        
        for (int i = 0; i < N; ++i) {
            int w = W[i];
            long long s = S[i];
            
            long long val = (w == idx1 ? mx2 : mx1) + s;
            if (val > dp[w]) {
                dp[w] = val;
                
                long long v1 = mx1, c1 = idx1;
                long long v2 = mx2, c2 = idx2;
                long long v3 = dp[w], c3 = w;
                
                if (v1 >= v2 && v1 >= v3) {
                    mx1 = v1; idx1 = c1;
                    long long cand2 = NEG_INF;
                    int cand2_idx = -1;
                    if (c2 != c1 && v2 > cand2) { cand2 = v2; cand2_idx = c2; }
                    if (c3 != c1 && v3 > cand2) { cand2 = v3; cand2_idx = c3; }
                    mx2 = cand2; idx2 = cand2_idx;
                } else if (v2 > v1 && v2 >= v3) {
                    mx1 = v2; idx1 = c2;
                    long long cand2 = NEG_INF;
                    int cand2_idx = -1;
                    if (c1 != c2 && v1 > cand2) { cand2 = v1; cand2_idx = c1; }
                    if (c3 != c2 && v3 > cand2) { cand2 = v3; cand2_idx = c3; }
                    mx2 = cand2; idx2 = cand2_idx;
                } else {
                    mx1 = v3; idx1 = c3;
                    long long cand2 = NEG_INF;
                    int cand2_idx = -1;
                    if (c1 != c3 && v1 > cand2) { cand2 = v1; cand2_idx = c1; }
                    if (c2 != c3 && v2 > cand2) { cand2 = v2; cand2_idx = c2; }
                    mx2 = cand2; idx2 = cand2_idx;
                }
            }
        }
        
        printf("%lld\n", mx1);
    }
    return 0;
}
