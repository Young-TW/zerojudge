#include <cstdio>
#include <vector>
#include <cstring>
using namespace std;

const int MOD = 998244353;

static char ibuf[1<<16];
static int ipos = 0, ilen = 0;

inline int readChar() {
    if (ipos >= ilen) {
        ilen = (int)fread(ibuf, 1, sizeof(ibuf), stdin);
        ipos = 0;
        if (ilen <= 0) return -1;
    }
    return ibuf[ipos++];
}

inline long long readInt() {
    int c = readChar();
    while (c != -1 && (c < '0' || c > '9') && c != '-') c = readChar();
    if (c == -1) return -1;
    int sgn = 1;
    if (c == '-') { sgn = -1; c = readChar(); }
    long long x = 0;
    while (c >= '0' && c <= '9') { x = x*10 + (c - '0'); c = readChar(); }
    return x * sgn;
}

static char obuf[1<<24];
static int opos = 0;

inline void writeInt(int x) {
    if (x == 0) { obuf[opos++] = '0'; return; }
    char tmp[12];
    int len = 0;
    while (x > 0) { tmp[len++] = (char)('0' + x%10); x /= 10; }
    while (len > 0) obuf[opos++] = tmp[--len];
}

int main() {
    long long n = readInt();
    if (n < 0) return 0;
    int N = (int)n;
    vector<int> a(N+1), b(N+1);
    for (int i = 1; i <= N; i++) a[i] = (int)readInt();
    for (int i = 1; i <= N; i++) b[i] = (int)readInt();
    
    vector<int> mu(N+1, 0);
    mu[1] = 1;
    {
        vector<int> primes;
        primes.reserve(N/10 + 10);
        vector<char> isComp(N+1, 0);
        for (int i = 2; i <= N; i++) {
            if (!isComp[i]) { primes.push_back(i); mu[i] = -1; }
            for (size_t j = 0; j < primes.size(); j++) {
                int p = primes[j];
                long long ip = (long long)i * p;
                if (ip > N) break;
                isComp[(int)ip] = 1;
                if (i % p == 0) { mu[(int)ip] = 0; break; }
                else mu[(int)ip] = -mu[i];
            }
        }
    }
    
    vector<int> A(N+1, 0), B(N+1, 0);
    for (int k = 1; k <= N; k++) {
        long long sa = 0, sb = 0;
        for (int m = k; m <= N; m += k) { sa += a[m]; sb += b[m]; }
        A[k] = (int)(sa % MOD);
        B[k] = (int)(sb % MOD);
    }
    
    vector<int> f(N+1);
    for (int k = 1; k <= N; k++) f[k] = (int)((long long)A[k] * B[k] % MOD);
    
    for (int k = 1; k <= N; k++) {
        long long s = 0;
        for (int d = 1; k*d <= N; d++) {
            int m = mu[d];
            if (m == 1) s += f[k*d];
            else if (m == -1) s -= f[k*d];
        }
        long long r = s % MOD;
        if (r < 0) r += MOD;
        writeInt((int)r);
        obuf[opos++] = (k < N) ? ' ' : '\n';
    }
    
    fwrite(obuf, 1, opos, stdout);
    return 0;
}
