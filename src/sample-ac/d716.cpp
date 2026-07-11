#include <cstdio>
#include <algorithm>

using namespace std;

const int MAX_N = 2000005;
int flakes[MAX_N];
int sorted_flakes[MAX_N];
int cnt[MAX_N];

const int BUF_SIZE = 1 << 20;
char buf[BUF_SIZE], *p1 = buf, *p2 = buf;

inline char gc() {
    if (p1 == p2) {
        p2 = (p1 = buf) + fread(buf, 1, BUF_SIZE, stdin);
        if (p1 == p2) return EOF;
    }
    return *p1++;
}

inline int readInt() {
    int x = 0;
    char c = gc();
    while (c < '0' || c > '9') {
        if (c == EOF) return EOF;
        c = gc();
    }
    while (c >= '0' && c <= '9') {
        x = x * 10 + (c - '0');
        c = gc();
    }
    return x;
}

int main() {
    int T = readInt();
    if (T < 0) return 0;
    
    while (T--) {
        int n = readInt();
        if (n < 0) break;
        
        for (int i = 0; i < n; ++i) {
            flakes[i] = readInt();
            sorted_flakes[i] = flakes[i];
        }
        
        sort(sorted_flakes, sorted_flakes + n);
        int m = unique(sorted_flakes, sorted_flakes + n) - sorted_flakes;
        
        for (int i = 0; i < n; ++i) {
            flakes[i] = lower_bound(sorted_flakes, sorted_flakes + m, flakes[i]) - sorted_flakes;
        }
        
        int left = 0;
        int max_len = 0;
        
        for (int i = 0; i < m; ++i) {
            cnt[i] = 0;
        }
        
        for (int right = 0; right < n; ++right) {
            cnt[flakes[right]]++;
            while (cnt[flakes[right]] > 1) {
                cnt[flakes[left]]--;
                left++;
            }
            if (right - left + 1 > max_len) {
                max_len = right - left + 1;
            }
        }
        
        printf("%d\n", max_len);
    }
    
    return 0;
}
