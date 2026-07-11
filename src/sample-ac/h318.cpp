#include <cstdio>
#include <cstring>
using namespace std;

typedef long long ll;
typedef unsigned long long ull;

const ll MOD = 998244353;
const ll INV2 = 499122177;

static char ibuf[1 << 16];
static int ipos = 0, ilen = 0;

inline int readChar() {
    if (ipos == ilen) {
        ilen = (int)fread(ibuf, 1, sizeof(ibuf), stdin);
        ipos = 0;
        if (ilen == 0) return -1;
    }
    return ibuf[ipos++];
}

inline bool readULL(ull &x) {
    int c;
    do {
        c = readChar();
        if (c == -1) return false;
    } while (c < '0' || c > '9');
    x = 0;
    while (c >= '0' && c <= '9') {
        x = x * 10 + (ull)(c - '0');
        c = readChar();
    }
    return true;
}

inline bool readInt(int &x) {
    int c;
    do {
        c = readChar();
        if (c == -1) return false;
    } while (c < '0' || c > '9');
    x = 0;
    while (c >= '0' && c <= '9') {
        x = x * 10 + (c - '0');
        c = readChar();
    }
    return true;
}

static char obuf[1 << 16];
static int opos = 0;

inline void flushOut() {
    if (opos > 0) {
        fwrite(obuf, 1, opos, stdout);
        opos = 0;
    }
}

inline void writeLL(ll x) {
    if (opos + 20 > (int)sizeof(obuf)) flushOut();
    if (x == 0) { obuf[opos++] = '0'; return; }
    if (x < 0) { obuf[opos++] = '-'; x = -x; }
    char tmp[20];
    int len = 0;
    while (x > 0) { tmp[len++] = '0' + (int)(x % 10); x /= 10; }
    while (len > 0) obuf[opos++] = tmp[--len];
}

int main() {
    int T;
    if (!readInt(T)) return 0;
    while (T--) {
        ull N;
        if (!readULL(N)) break;
        ll n = (ll)(N % (ull)MOD);
        ll np1 = (ll)((N + 1ULL) % (ull)MOD);
        ll ans = (ll)((ull)n * (ull)np1 % (ull)MOD);
        ans = (ll)((ull)ans * (ull)INV2 % (ull)MOD);
        writeLL(ans);
        obuf[opos++] = '\n';
    }
    flushOut();
    return 0;
}
