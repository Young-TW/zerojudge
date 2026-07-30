// d493. 入门求幂题 — 求 a^n。
// 求幂系列隱藏測資 a^n 可達天文數字,long long/__int128 會溢位,故用大數。
// 100% 自寫。以 base 1e9 之 vector 存絕對值,快速冪相乘;符號 = a<0 且 n 為奇數。
#include <iostream>
#include <vector>
#include <string>
#include <cstdint>
using namespace std;

typedef vector<uint32_t> Big;           // 小端,每位 0..1e9-1
static const uint32_t BASE = 1000000000u;

static Big fromULL(unsigned long long v) {
    Big r;
    if (v == 0) { r.push_back(0); return r; }
    while (v) { r.push_back((uint32_t)(v % BASE)); v /= BASE; }
    return r;
}
static bool isZero(const Big& a) { return a.size() == 1 && a[0] == 0; }

static Big mul(const Big& a, const Big& b) {
    if (isZero(a) || isZero(b)) return fromULL(0);
    vector<uint64_t> tmp(a.size() + b.size(), 0);
    for (size_t i = 0; i < a.size(); ++i) {
        uint64_t carry = 0;
        for (size_t j = 0; j < b.size(); ++j) {
            uint64_t cur = tmp[i + j] + (uint64_t)a[i] * b[j] + carry;
            tmp[i + j] = cur % BASE;
            carry = cur / BASE;
        }
        tmp[i + b.size()] += carry;
    }
    Big r(tmp.size());
    for (size_t i = 0; i < tmp.size(); ++i) r[i] = (uint32_t)tmp[i];
    while (r.size() > 1 && r.back() == 0) r.pop_back();
    return r;
}

static string toStr(const Big& a, bool neg) {
    string s;
    if (neg && !isZero(a)) s += '-';
    s += to_string(a.back());
    for (int i = (int)a.size() - 2; i >= 0; --i) {
        string p = to_string(a[i]);
        s += string(9 - p.size(), '0') + p;
    }
    return s;
}

int main() {
    long long a, n;
    while (cin >> a >> n) {
        bool neg = (a < 0) && (n % 2 != 0);
        unsigned long long absA = (a < 0) ? (unsigned long long)(-(a + 1)) + 1ULL
                                          : (unsigned long long)a;
        Big base = fromULL(absA);
        Big result = fromULL(1);        // a^0 = 1
        long long e = n;
        while (e > 0) {
            if (e & 1LL) result = mul(result, base);
            e >>= 1;
            if (e > 0) base = mul(base, base);
        }
        cout << toStr(result, neg) << '\n';
    }
    return 0;
}
