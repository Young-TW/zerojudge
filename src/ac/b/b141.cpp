#include <bits/stdc++.h>
using namespace std;
struct BigInt {
static const uint32_t BASE = 1000000000U;
vector<uint32_t> d;
BigInt() {}
BigInt(uint64_t v) { *this = v; }
BigInt& operator=(uint64_t v) {
d.clear();
if (v == 0) return *this;
while (v) {
d.push_back(v % BASE);
v /= BASE;
}
return *this;
}
static BigInt fromString(const string& s) {
BigInt res(0);
for (char ch : s) {
uint32_t digit = ch - '0';
res = mul_small(res, 10);
res = add_small(res, digit);
}
return res;
}
bool isZero() const { return d.empty(); }
void trim() {
while (!d.empty() && d.back() == 0) d.pop_back();
}
friend bool operator<(const BigInt& a, const BigInt& b) {
if (a.d.size() != b.d.size()) return a.d.size() < b.d.size();
for (int i = (int)a.d.size() - 1; i >= 0; --i)
if (a.d[i] != b.d[i]) return a.d[i] < b.d[i];
return false;
}
friend bool operator==(const BigInt& a, const BigInt& b) { return a.d == b.d; }
friend bool operator!=(const BigInt& a, const BigInt& b) { return !(a == b); }
friend bool operator>(const BigInt& a, const BigInt& b) { return b < a; }
friend bool operator<=(const BigInt& a, const BigInt& b) { return !(b < a); }
friend bool operator>=(const BigInt& a, const BigInt& b) { return !(a < b); }
static BigInt add_small(const BigInt& a, uint32_t v) {
BigInt res = a;
uint64_t carry = v;
size_t i = 0;
while (carry) {
if (i == res.d.size()) res.d.push_back(0);
uint64_t sum = (uint64_t)res.d[i] + carry;
res.d[i] = sum % BASE;
carry = sum / BASE;
++i;
}
return res;
}
static BigInt mul_small(const BigInt& a, uint32_t m) {
if (a.isZero() || m == 0) return BigInt(0);
BigInt res;
res.d.resize(a.d.size());
uint64_t carry = 0;
for (size_t i = 0; i < a.d.size(); ++i) {
uint64_t cur = (uint64_t)a.d[i] * m + carry;
res.d[i] = cur % BASE;
carry = cur / BASE;
}
if (carry) res.d.push_back(carry);
return res;
}
static BigInt div_small(const BigInt& a, uint32_t v, uint32_t& rem) {
BigInt q;
q.d.resize(a.d.size());
uint64_t cur = 0;
for (int i = (int)a.d.size() - 1; i >= 0; --i) {
cur = cur * BASE + a.d[i];
q.d[i] = cur / v;
cur %= v;
}
rem = (uint32_t)cur;
q.trim();
return q;
}
static BigInt sub(const BigInt& a, const BigInt& b) {
BigInt res = a;
int64_t carry = 0;
for (size_t i = 0; i < res.d.size(); ++i) {
int64_t cur = (int64_t)res.d[i] - carry -
(i < b.d.size() ? b.d[i] : 0);
if (cur < 0) {
cur += BASE;
carry = 1;
} else carry = 0;
res.d[i] = (uint32_t)cur;
}
res.trim();
return res;
}
static BigInt mul(const BigInt& a, const BigInt& b) {
if (a.isZero() || b.isZero()) return BigInt(0);
BigInt res;
res.d.assign(a.d.size() + b.d.size(), 0);
for (size_t i = 0; i < a.d.size(); ++i) {
uint64_t carry = 0;
for (size_t j = 0; j < b.d.size() || carry; ++j) {
uint64_t cur = res.d[i + j] +
(uint64_t)a.d[i] *
(j < b.d.size() ? b.d[j] : 0) +
carry;
res.d[i + j] = cur % BASE;
carry = cur / BASE;
}
}
res.trim();
return res;
}
static void div_mod(const BigInt& a, const BigInt& b,
BigInt& q, BigInt& r) {
q.d.assign(a.d.size(), 0);
r = BigInt(0);
for (int i = (int)a.d.size() - 1; i >= 0; --i) {
r = mul_small(r, BASE);
if (!r.isZero() || a.d[i] != 0) r = add_small(r, a.d[i]);
uint32_t low = 0, high = BASE - 1, best = 0;
while (low <= high) {
uint32_t mid = (low + high) >> 1;
BigInt t = mul_small(b, mid);
if (t <= r) {
best = mid;
low = mid + 1;
} else high = mid - 1;
}
q.d[i] = best;
if (best) r = sub(r, mul_small(b, best));
}
q.trim();
r.trim();
}
static BigInt mod(const BigInt& a, const BigInt& b) {
BigInt q, r;
div_mod(a, b, q, r);
return r;
}
static BigInt div_exact(const BigInt& a, const BigInt& b) {
BigInt q, r;
div_mod(a, b, q, r);
return q;
}
static BigInt gcd(BigInt a, BigInt b) {
while (!b.isZero()) {
BigInt r = mod(a, b);
a = b;
b = r;
}
return a;
}
static BigInt pow_mod(BigInt base, BigInt exp, const BigInt& modv) {
BigInt result(1);
base = mod(base, modv);
while (!exp.isZero()) {
uint32_t rem = exp.d.empty() ? 0 : (exp.d[0] & 1U);
if (rem) result = mod(mul(result, base), modv);
uint32_t carry = 0;
for (int i = (int)exp.d.size() - 1; i >= 0; --i) {
uint64_t cur = (uint64_t)carry * BASE + exp.d[i];
exp.d[i] = (uint32_t)(cur >> 1);
carry = (uint32_t)(cur & 1U);
}
exp.trim();
if (!exp.isZero())
base = mod(mul(base, base), modv);
}
return result;
}
string toString() const {
if (isZero()) return "0";
string s;
BigInt tmp = *this;
while (!tmp.isZero()) {
uint32_t rem;
tmp = div_small(tmp, 10, rem);
s.push_back(char('0' + rem));
}
reverse(s.begin(), s.end());
return s;
}
};
BigInt pow_small(uint32_t base, int exp) {
BigInt res(1);
BigInt b(base);
while (exp) {
if (exp & 1) res = BigInt::mul(res, b);
b = BigInt::mul(b, b);
exp >>= 1;
}
return res;
}
BigInt order_mod_prime_power(const BigInt& n_mod, const BigInt& mod,
int k, int prime) {
int e2 = 0, e5 = 0;
if (prime == 2) {
e2 = k - 1;
} else {
e2 = 2;
e5 = k - 1;
}
BigInt ord = pow_small(2, e2);
if (e5) ord = BigInt::mul(ord, pow_small(5, e5));
while (e2 > 0) {
uint32_t rem;
BigInt cand = BigInt::div_small(ord, 2, rem);
if (BigInt::pow_mod(n_mod, cand, mod) == BigInt(1)) {
ord = cand;
--e2;
} else break;
}
while (e5 > 0) {
uint32_t rem;
BigInt cand = BigInt::div_small(ord, 5, rem);
if (BigInt::pow_mod(n_mod, cand, mod) == BigInt(1)) {
ord = cand;
--e5;
} else break;
}
return ord;
}
int main() {
ios::sync_with_stdio(false);
cin.tie(nullptr);
string n_str;
int k;
while (cin >> n_str >> k) {
BigInt mod2 = pow_small(2, k);
BigInt mod5 = pow_small(5, k);
BigInt n = BigInt::fromString(n_str);
int cnt2 = 0;
{
BigInt tmp = n;
while (true) {
uint32_t rem;
BigInt q = BigInt::div_small(tmp, 2, rem);
if (rem == 0) {
++cnt2;
tmp = q;
} else break;
}
}
int cnt5 = 0;
{
BigInt tmp = n;
while (true) {
uint32_t rem;
BigInt q = BigInt::div_small(tmp, 5, rem);
if (rem == 0) {
++cnt5;
tmp = q;
} else break;
}
}
if ( (cnt2 > 0 && cnt2 < k) || (cnt5 > 0 && cnt5 < k) ) {
cout << -1 << '\n';
continue;
}
BigInt per2;
if (cnt2 >= k) per2 = BigInt(1);
else {
BigInt n2 = BigInt::mod(n, mod2);
per2 = order_mod_prime_power(n2, mod2, k, 2);
}
BigInt per5;
if (cnt5 >= k) per5 = BigInt(1);
else {
BigInt n5 = BigInt::mod(n, mod5);
per5 = order_mod_prime_power(n5, mod5, k, 5);
}
BigInt g = BigInt::gcd(per2, per5);
BigInt t = BigInt::div_exact(per2, g);
BigInt ans = BigInt::mul(t, per5);
cout << ans.toString() << '\n';
}
return 0;
}
