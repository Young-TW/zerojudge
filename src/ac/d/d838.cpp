#include <iostream>
#include <array>
#include <cstdint>
#include <cstdio>
#include <string>

using namespace std;

const int BASE = 10000;
const int LIMBS = 125; // 500 / 4

struct BigInt {
    array<uint32_t, LIMBS> d;
    BigInt() { d.fill(0); }
    static BigInt from_uint(uint32_t x) {
        BigInt r;
        r.d[0] = x;
        return r;
    }
};

BigInt multiply(const BigInt& a, const BigInt& b) {
    BigInt res;
    uint64_t carry = 0;
    for (int k = 0; k < LIMBS; ++k) {
        uint64_t sum = carry;
        for (int i = 0; i <= k; ++i) {
            sum += static_cast<uint64_t>(a.d[i]) * b.d[k - i];
        }
        res.d[k] = static_cast<uint32_t>(sum % BASE);
        carry = sum / BASE;
    }
    return res;
}

BigInt pow2_mod(int P) {
    BigInt result = BigInt::from_uint(1);
    BigInt base = BigInt::from_uint(2);
    while (P > 0) {
        if (P & 1) result = multiply(result, base);
        base = multiply(base, base);
        P >>= 1;
    }
    return result;
}

void subtract_one(BigInt& a) {
    for (int i = 0; i < LIMBS; ++i) {
        if (a.d[i] > 0) {
            a.d[i]--;
            break;
        } else {
            a.d[i] = BASE - 1;
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // log10(2) * 10^25, truncated
    const char* log10_2_str = "3010299956639811952137388";
    __int128 LOG10_2_SCALED = 0;
    for (int i = 0; log10_2_str[i]; ++i) {
        LOG10_2_SCALED = LOG10_2_SCALED * 10 + (log10_2_str[i] - '0');
    }
    const __int128 SCALE = (__int128)1000000000000000000ULL * 10000000ULL; // 10^25

    int P;
    while (cin >> P) {
        // Number of digits of 2^P - 1
        __int128 product = static_cast<__int128>(P) * LOG10_2_SCALED;
        long long digits = static_cast<long long>(product / SCALE) + 1;
        cout << digits << '\n';

        // Last 500 digits of 2^P - 1
        BigInt res = pow2_mod(P);
        subtract_one(res);

        string s;
        s.reserve(500);
        char buf[5];
        for (int i = LIMBS - 1; i >= 0; --i) {
            snprintf(buf, sizeof(buf), "%04u", res.d[i]);
            s += buf;
        }

        for (int i = 0; i < 10; ++i) {
            cout << s.substr(i * 50, 50) << '\n';
        }
    }
    return 0;
}
