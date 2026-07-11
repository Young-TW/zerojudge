#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

typedef vector<int> BigInt;

void mul(BigInt& v, int x) {
    if (x == 0) { v.assign(1, 0); return; }
    int carry = 0;
    for (int i = 0; i < v.size(); i++) {
        carry += v[i] * x;
        v[i] = carry % 10;
        carry /= 10;
    }
    while (carry) {
        v.push_back(carry % 10);
        carry /= 10;
    }
}

int cmp(const BigInt& a, const BigInt& b) {
    if (a.size() != b.size()) return a.size() < b.size() ? -1 : 1;
    for (int i = a.size() - 1; i >= 0; i--) {
        if (a[i] != b[i]) return a[i] < b[i] ? -1 : 1;
    }
    return 0;
}

void sub(BigInt& a, const BigInt& b) {
    int borrow = 0;
    for (int i = 0; i < a.size(); i++) {
        int val = a[i] - borrow - (i < b.size() ? b[i] : 0);
        if (val < 0) {
            val += 10;
            borrow = 1;
        } else {
            borrow = 0;
        }
        a[i] = val;
    }
    while (a.size() > 1 && a.back() == 0) a.pop_back();
}

BigInt mod(BigInt A, const BigInt& M) {
    if (cmp(A, M) < 0) return A;
    BigInt rem = A;
    while (cmp(rem, M) >= 0) {
        BigInt shifted_M = M;
        int shift = rem.size() - shifted_M.size();
        if (shift > 0) {
            shifted_M.insert(shifted_M.begin(), shift, 0);
            if (cmp(rem, shifted_M) < 0) {
                shifted_M.erase(shifted_M.begin());
            }
        }
        while (cmp(rem, shifted_M) >= 0) {
            sub(rem, shifted_M);
        }
    }
    return rem;
}

void print(const BigInt& v) {
    string s = "";
    for (int i = v.size() - 1; i >= 0; i--) {
        s += to_string(v[i]);
    }
    string out = "";
    int n = s.length();
    for (int i = 0; i < n; i++) {
        if (i > 0 && (n - i) % 3 == 0) {
            out += ' ';
        }
        out += s[i];
    }
    cout << out << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int a, b, c, d;
    while (cin >> a >> b >> c >> d) {
        BigInt A;
        A.assign(1, 1);
        for (int i = 0; i < b; i++) {
            mul(A, a);
        }

        BigInt M;
        M.assign(1, 1);
        for (int i = 0; i < d; i++) {
            mul(M, c);
        }

        if (M.size() == 1 && M[0] == 0) {
            cout << 0 << "\n";
            continue;
        }

        BigInt rem = mod(A, M);
        print(rem);
    }
    return 0;
}
