#include <cstdio>
#include <vector>

using namespace std;

inline long long readLL() {
    long long x = 0;
    char c = getchar();
    while (c < '0' || c > '9') c = getchar();
    while (c >= '0' && c <= '9') {
        x = x * 10 + (c - '0');
        c = getchar();
    }
    return x;
}

int main() {
    int N = (int)readLL();
    int K = (int)readLL();
    long long G = readLL();
    
    vector<long long> P(N);
    for (int i = 0; i < N; ++i) {
        P[i] = readLL();
    }
    
    vector<int> max_q(N);
    vector<int> min_q(N);
    int max_head = 0, max_tail = 0;
    int min_head = 0, min_tail = 0;
    long long ans = 0;
    
    for (int i = 0; i < N; ++i) {
        while (max_head < max_tail && P[max_q[max_tail - 1]] <= P[i]) {
            max_tail--;
        }
        max_q[max_tail++] = i;
        
        while (min_head < min_tail && P[min_q[min_tail - 1]] >= P[i]) {
            min_tail--;
        }
        min_q[min_tail++] = i;
        
        if (i >= K - 1) {
            while (max_head < max_tail && max_q[max_head] <= i - K) {
                max_head++;
            }
            while (min_head < min_tail && min_q[min_head] <= i - K) {
                min_head++;
            }
            
            if (P[max_q[max_head]] - P[min_q[min_head]] <= G) {
                ans++;
            }
        }
    }
    
    printf("%lld\n", ans);
    return 0;
}
