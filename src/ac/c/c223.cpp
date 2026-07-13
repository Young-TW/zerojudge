#include <cstdio>
#include <cstring>

using namespace std;

const int MAX_VAL = 1000000;
int cnt[MAX_VAL + 1];
long long q1[MAX_VAL + 5];
long long q2[MAX_VAL + 5];

char ibuf[1 << 20];
int ipos = 0, ilen = 0;

inline int gc() {
    if (ipos == ilen) {
        ilen = fread(ibuf, 1, sizeof(ibuf), stdin);
        ipos = 0;
        if (ilen == 0) return EOF;
    }
    return ibuf[ipos++];
}

inline long long readInt() {
    int c = gc();
    while (c < '0' || c > '9') {
        if (c == EOF) return -1;
        c = gc();
    }
    long long x = 0;
    while (c >= '0' && c <= '9') {
        x = x * 10 + (c - '0');
        c = gc();
    }
    return x;
}

int main() {
    long long n;
    while ((n = readInt()) > 0) {
        memset(cnt, 0, sizeof(cnt));
        for (int i = 0; i < n; ++i) {
            long long x = readInt();
            cnt[x]++;
        }
        
        int head1 = 0, tail1 = 0, head2 = 0, tail2 = 0;
        for (int i = 1; i <= MAX_VAL; ++i) {
            while (cnt[i] > 0) {
                q1[tail1++] = i;
                cnt[i]--;
            }
        }
        
        long long total_cost = 0;
        for (int i = 1; i < n; ++i) {
            long long a, b;
            
            if (head1 == tail1) {
                a = q2[head2++];
            } else if (head2 == tail2) {
                a = q1[head1++];
            } else {
                if (q1[head1] <= q2[head2]) a = q1[head1++];
                else a = q2[head2++];
            }
            
            if (head1 == tail1) {
                b = q2[head2++];
            } else if (head2 == tail2) {
                b = q1[head1++];
            } else {
                if (q1[head1] <= q2[head2]) b = q1[head1++];
                else b = q2[head2++];
            }
            
            long long sum = a + b;
            total_cost += sum;
            q2[tail2++] = sum;
        }
        printf("%lld\n", total_cost);
    }
    return 0;
}
