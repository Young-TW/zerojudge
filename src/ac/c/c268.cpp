#include <bits/stdc++.h>
using namespace std;

/* fast scanner using fread */
class FastScanner {
    static const size_t BUFSIZE = 1 << 20;
    char buf[BUFSIZE];
    size_t idx, sz;
public:
    FastScanner() : idx(0), sz(0) {}
    inline char nextChar() {
        if (idx >= sz) {
            sz = fread(buf, 1, BUFSIZE, stdin);
            idx = 0;
            if (sz == 0) return EOF;
        }
        return buf[idx++];
    }
    template <class T>
    bool nextInt(T &out) {
        char c; T sign = 1; T val = 0;
        c = nextChar();
        if (c == EOF) return false;
        while (c!='-' && (c<'0' || c>'9')) {
            c = nextChar();
            if (c == EOF) return false;
        }
        if (c == '-') { sign = -1; c = nextChar(); }
        for ( ; c>='0' && c<='9'; c = nextChar())
            val = val*10 + (c - '0');
        out = val * sign;
        return true;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    FastScanner fs;
    int T;
    if (!fs.nextInt(T)) return 0;
    const int LIMIT = 45;               // 45 => always YES
    while (T--) {
        long long n;
        fs.nextInt(n);
        if (n >= LIMIT) {
            long long dummy;
            for (long long i = 0; i < n; ++i) fs.nextInt(dummy); // discard
            puts("YES");
            continue;
        }
        // n <= 44
        vector<long long> a;
        a.reserve(static_cast<size_t>(n));
        long long x;
        for (long long i = 0; i < n; ++i) {
            fs.nextInt(x);
            a.push_back(x);
        }
        if (n < 3) {
            puts("NO");
            continue;
        }
        sort(a.begin(), a.end());
        bool ok = false;
        for (size_t i = 0; i + 2 < a.size(); ++i) {
            if (a[i] + a[i+1] > a[i+2]) {
                ok = true;
                break;
            }
        }
        puts(ok ? "YES" : "NO");
    }
    return 0;
}
