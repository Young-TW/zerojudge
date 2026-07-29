#include <bits/stdc++.h>
using namespace std;

/* ---------- big integer, base 1e9 ---------- */
const uint32_t BASE = 1000000000U;          // 10^9
using Big = vector<uint32_t>;               // little endian, no leading zeros (except zero)

void trim(Big &a) {
    while (a.size() > 1 && a.back() == 0) a.pop_back();
}

int cmp(const Big &a, const Big &b) {       // -1,0,1
    if (a.size() != b.size()) return a.size() < b.size() ? -1 : 1;
    for (int i = (int)a.size() - 1; i >= 0; --i)
        if (a[i] != b[i]) return a[i] < b[i] ? -1 : 1;
    return 0;
}

Big add(const Big &a, const Big &b) {
    Big res;
    uint64_t carry = 0;
    size_t n = max(a.size(), b.size());
    res.reserve(n + 1);
    for (size_t i = 0; i < n || carry; ++i) {
        uint64_t cur = carry;
        if (i < a.size()) cur += a[i];
        if (i < b.size()) cur += b[i];
        res.push_back(uint32_t(cur % BASE));
        carry = cur / BASE;
    }
    trim(res);
    return res;
}

// a >= b
Big sub(const Big &a, const Big &b) {
    Big res = a;
    int64_t borrow = 0;
    for (size_t i = 0; i < res.size(); ++i) {
        int64_t cur = (int64_t)res[i] - borrow - (i < b.size() ? b[i] : 0);
        if (cur < 0) {
            cur += BASE;
            borrow = 1;
        } else {
            borrow = 0;
        }
        res[i] = (uint32_t)cur;
    }
    trim(res);
    return res;
}

/* ---------- Fibonacci weights: f[0]=1, f[1]=2, f[i]=f[i-1]+f[i-2] ---------- */
/* Zeckendorf digit positions map to distinct weights 1,2,3,5,8,...          */
const int MAX_FIB = 250;
vector<Big> fib;   // fib[i] = weight of digit position i (from the right)

void build_fib() {
    fib.resize(MAX_FIB + 1);
    fib[0] = Big{1};
    fib[1] = Big{2};
    for (int i = 2; i <= MAX_FIB; ++i) {
        fib[i] = add(fib[i - 1], fib[i - 2]);
    }
}

/* ---------- conversion: Zeckendorf string -> big integer ---------- */
Big zeck_to_big(const string &s) {
    Big val{0};
    int n = (int)s.size();
    for (int i = 0; i < n; ++i) {
        if (s[n - 1 - i] == '1') {          // rightmost char is index 0
            val = add(val, fib[i]);
        }
    }
    return val;
}

/* ---------- conversion: big integer -> Zeckendorf string ---------- */
string big_to_zeck(Big num) {
    // special case 1 -> "1"
    if (cmp(num, fib[0]) == 0) return "1";

    int hi = (int)fib.size() - 1;
    while (hi > 0 && cmp(fib[hi], num) > 0) --hi;

    vector<char> bits(hi + 1, '0');
    int i = hi;
    while (i >= 0) {
        if (cmp(fib[i], num) <= 0) {
            bits[i] = '1';
            num = sub(num, fib[i]);
            i -= 2;                         // skip neighbour
        } else {
            --i;
        }
    }

    // remove leading zeros
    int first = (int)bits.size() - 1;
    while (first > 0 && bits[first] == '0') --first;
    string out;
    out.reserve(first + 1);
    for (int j = first; j >= 0; --j) out.push_back(bits[j]);
    return out;
}

/* ---------- main ---------- */
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    build_fib();

    string a, b;
    bool first = true;
    while (cin >> a >> b) {
        if (!first) cout << "\n";
        first = false;

        Big A = zeck_to_big(a);
        Big B = zeck_to_big(b);
        Big S = add(A, B);
        cout << big_to_zeck(S) << "\n";
    }
    return 0;
}
