#include <iostream>
#include <string>
#include <vector>
#include <cctype>
using namespace std;

typedef unsigned long long UINT64;

UINT64 mul(UINT64 a, UINT64 b, UINT64 mod) {
    UINT64 ret = 0;
    a %= mod;
    b %= mod;
    while (b) {
        if (b & 1) {
            ret += a;
            if (ret >= mod) ret -= mod;
        }
        a <<= 1;
        if (a >= mod) a -= mod;
        b >>= 1;
    }
    return ret;
}

UINT64 mpow(UINT64 x, UINT64 y, UINT64 mod) {
    if (mod == 1) return 0;
    UINT64 ret = 1;
    x %= mod;
    while (y) {
        if (y & 1)
            ret = mul(ret, x, mod);
        y >>= 1;
        x = mul(x, x, mod);
    }
    return ret;
}

UINT64 fast_pow(string s, UINT64 x, UINT64 z) {
    if (z == 1) return 0;
    UINT64 y = 0;
    for (char c : s) {
        y = (y << 1) | (c - '0');
    }
    return mpow(x, y, z);
}

UINT64 optimized_pow(string s, UINT64 x, UINT64 z) {
    if (z == 1) return 0;
    int n = s.size();
    vector<UINT64> pow2(n + 1);
    pow2[0] = 1;
    for (int i = 1; i <= n; ++i) {
        pow2[i] = mul(pow2[i-1], pow2[i-1], z);
    }

    UINT64 result = 1;
    UINT64 base = x % z;
    for (int i = 0; i < n; ++i) {
        if (s[i] == '1') {
            UINT64 exponent = 1ULL << (n - 1 - i);
            UINT64 temp = mpow(base, exponent, z);
            result = mul(result, temp, z);
        }
    }
    return result;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    string x_str, y_str, z_str;
    while (cin >> x_str >> y_str >> z_str) {
        UINT64 x = 0, z = 0;
        for (char c : x_str) {
            x = x * 10 + (c - '0');
        }
        for (char c : z_str) {
            z = z * 10 + (c - '0');
        }

        if (y_str == "0") {
            cout << "1\n";
            continue;
        }

        UINT64 res = optimized_pow(y_str, x, z);
        cout << res << '\n';
    }

    return 0;
}
