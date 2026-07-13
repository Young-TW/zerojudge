#include <cstdio>
#include <cstring>

int cnt[30001];

inline int readInt() {
    int x = 0;
    char c = getchar();
    while (c != EOF && (c < '0' || c > '9')) {
        c = getchar();
    }
    if (c == EOF) return -1;
    while (c >= '0' && c <= '9') {
        x = x * 10 + (c - '0');
        c = getchar();
    }
    return x;
}

int main() {
    int t = readInt();
    while (t--) {
        int r = readInt();
        memset(cnt, 0, sizeof(cnt));
        for (int i = 0; i < r; ++i) {
            int s = readInt();
            cnt[s]++;
        }
        
        int median = 0;
        int target = (r - 1) / 2;
        int sum_cnt = 0;
        for (int i = 0; i <= 30000; ++i) {
            sum_cnt += cnt[i];
            if (sum_cnt > target) {
                median = i;
                break;
            }
        }
        
        long long dist_sum = 0;
        for (int i = 0; i <= 30000; ++i) {
            if (cnt[i] > 0) {
                dist_sum += (long long)cnt[i] * (i > median ? i - median : median - i);
            }
        }
        
        printf("%lld %d\n", dist_sum, median);
    }
    return 0;
}
