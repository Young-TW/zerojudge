#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

typedef long long ll;
typedef vector<int> vi;

const ll P = 998244353;
const ll G = 3;

ll pow_mod(ll a, ll b, ll p) {
    ll res = 1;
    a %= p;
    while(b) {
        if(b & 1) res = res * a % p;
        a = a * a % p;
        b >>= 1;
    }
    return res;
}

void ntt(vi &a, bool invert) {
    int n = a.size();
    for (int i = 1, j = 0; i < n; i++) {
        int bit = n >> 1;
        for (; j & bit; bit >>= 1) j ^= bit;
        j ^= bit;
        if (i < j) swap(a[i], a[j]);
    }
    for (int len = 2; len <= n; len <<= 1) {
        ll w = invert ? pow_mod(G, P - 1 - (P - 1) / len, P) : pow_mod(G, (P - 1) / len, P);
        for (int i = 0; i < n; i += len) {
            ll wn = 1;
            for (int j = 0; j < len / 2; j++) {
                ll u = a[i+j];
                ll v = (ll)a[i+j + len/2] * wn % P;
                ll sum = u + v;
                if (sum >= P) sum -= P;
                ll diff = u - v;
                if (diff < 0) diff += P;
                a[i+j] = sum;
                a[i+j + len/2] = diff;
                wn = wn * w % P;
            }
        }
    }
    if (invert) {
        ll n_inv = pow_mod(n, P - 2, P);
        for (int &x : a) {
            x = (ll)x * n_inv % P;
        }
    }
}

string add(string s1, string s2) {
    if (s1.length() < s2.length()) swap(s1, s2);
    int n1 = s1.length(), n2 = s2.length();
    string res = "";
    int carry = 0;
    for (int i = 0; i < n1; i++) {
        int d1 = s1[n1 - 1 - i] - '0';
        int d2 = (i < n2) ? s2[n2 - 1 - i] - '0' : 0;
        int sum = d1 + d2 + carry;
        res += (sum % 10) + '0';
        carry = sum / 10;
    }
    if (carry) res += carry + '0';
    reverse(res.begin(), res.end());
    return res;
}

string sub(string s1, string s2) {
    int n1 = s1.length(), n2 = s2.length();
    string res = "";
    int borrow = 0;
    for (int i = 0; i < n1; i++) {
        int d1 = s1[n1 - 1 - i] - '0';
        int d2 = (i < n2) ? s2[n2 - 1 - i] - '0' : 0;
        int diff = d1 - d2 - borrow;
        if (diff < 0) {
            diff += 10;
            borrow = 1;
        } else {
            borrow = 0;
        }
        res += diff + '0';
    }
    while (res.length() > 1 && res.back() == '0') {
        res.pop_back();
    }
    reverse(res.begin(), res.end());
    return res;
}

string mul(string s1, string s2) {
    if (s1 == "0" || s2 == "0") return "0";
    int n1 = s1.length(), n2 = s2.length();
    int n = 1;
    while (n < n1 + n2) n <<= 1;
    
    vi a(n, 0), b(n, 0);
    for (int i = 0; i < n1; i++) a[i] = s1[n1 - 1 - i] - '0';
    for (int i = 0; i < n2; i++) b[i] = s2[n2 - 1 - i] - '0';
    
    ntt(a, false);
    ntt(b, false);
    
    for (int i = 0; i < n; i++) {
        a[i] = (ll)a[i] * b[i] % P;
    }
    
    ntt(a, true);
    
    string res = "";
    ll carry = 0;
    for (int i = 0; i < n; i++) {
        ll val = a[i] + carry;
        res += (val % 10) + '0';
        carry = val / 10;
    }
    while (carry) {
        res += (carry % 10) + '0';
        carry /= 10;
    }
    while (res.length() > 1 && res.back() == '0') {
        res.pop_back();
    }
    reverse(res.begin(), res.end());
    return res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    string a, b;
    char op;
    while (cin >> a >> op >> b) {
        if (op == '+') {
            cout << add(a, b) << "\n";
        } else if (op == '-') {
            cout << sub(a, b) << "\n";
        } else if (op == '*') {
            cout << mul(a, b) << "\n";
        }
    }
    
    return 0;
}
