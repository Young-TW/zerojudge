#include <vector>
#include <algorithm>
#include <cstdio>

using namespace std;

const int MAX_A = 100005;
const int BUFFER_SIZE = 1 << 20;
char buffer[BUFFER_SIZE];
int buffer_pos = 0;
int buffer_len = 0;

inline char get_char() {
    if (buffer_pos == buffer_len) {
        buffer_len = fread(buffer, 1, BUFFER_SIZE, stdin);
        buffer_pos = 0;
        if (buffer_len == 0) return EOF;
    }
    return buffer[buffer_pos++];
}

inline bool readInt(int &x) {
    x = 0;
    char c = get_char();
    while (c < '0' || c > '9') {
        if (c == EOF) return false;
        c = get_char();
    }
    while (c >= '0' && c <= '9') {
        x = x * 10 + (c - '0');
        c = get_char();
    }
    return true;
}

int main() {
    int n, k;
    while (readInt(n)) {
        if (!readInt(k)) break;
        
        vector<int> a(n + 1);
        for (int i = 1; i <= n; ++i) {
            readInt(a[i]);
        }
        
        vector<int> dp_prev(n + 1, 0);
        vector<int> dp_curr(n + 1, 0);
        vector<int> cnt(MAX_A, 0);
        vector<int> dq(n + 1);
        
        for (int j = 1; j <= k; ++j) {
            fill(cnt.begin(), cnt.end(), 0);
            int head = 0, tail = 0;
            int left = 1;
            
            for (int i = 1; i <= n; ++i) {
                cnt[a[i]]++;
                while (cnt[a[i]] > 1) {
                    cnt[a[left]]--;
                    left++;
                }
                
                while (head < tail && dp_prev[dq[tail - 1]] - dq[tail - 1] <= dp_prev[i - 1] - (i - 1)) {
                    tail--;
                }
                dq[tail++] = i - 1;
                
                while (head < tail && dq[head] < left - 1) {
                    head++;
                }
                
                int p = dq[head];
                dp_curr[i] = max(dp_curr[i - 1], dp_prev[p] - p + i);
            }
            swap(dp_prev, dp_curr);
        }
        
        printf("%d\n", dp_prev[n]);
    }
    
    return 0;
}
