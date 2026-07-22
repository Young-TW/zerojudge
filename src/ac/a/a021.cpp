#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

typedef vector<int> BigInt;

BigInt fromStr(const string& s) {
    BigInt b;
    for (int i = (int)s.size() - 1; i >= 0; i--) {
        b.push_back(s[i] - '0');
    }
    while (b.size() > 1 && b.back() == 0) b.pop_back();
    return b;
}

string toStr(const BigInt& b) {
    string s;
    for (int i = (int)b.size() - 1; i >= 0; i--) {
        s += (char)('0' + b[i]);
    }
    return s;
}

bool lessThan(const BigInt& a, const BigInt& b) {
    if (a.size() != b.size()) return a.size() < b.size();
    for (int i = (int)a.size() - 1; i >= 0; i--) {
        if (a[i] != b[i]) return a[i] < b[i];
    }
    return false;
}

BigInt add(const BigInt& a, const BigInt& b) {
    BigInt c;
    int carry = 0;
    int n = max(a.size(), b.size());
    for (int i = 0; i < n || carry; i++) {
        int sum = carry;
        if (i < (int)a.size()) sum += a[i];
        if (i < (int)b.size()) sum += b[i];
        c.push_back(sum % 10);
        carry = sum / 10;
    }
    return c;
}

BigInt sub(const BigInt& a, const BigInt& b) {
    BigInt c;
    int borrow = 0;
    for (int i = 0; i < (int)a.size(); i++) {
        int diff = a[i] - borrow - (i < (int)b.size() ? b[i] : 0);
        if (diff < 0) {
            diff += 10;
            borrow = 1;
        } else {
            borrow = 0;
        }
        c.push_back(diff);
    }
    while (c.size() > 1 && c.back() == 0) c.pop_back();
    return c;
}

BigInt mul(const BigInt& a, const BigInt& b) {
    BigInt c(a.size() + b.size(), 0);
    for (int i = 0; i < (int)a.size(); i++) {
        int carry = 0;
        for (int j = 0; j < (int)b.size() || carry; j++) {
            int cur = c[i + j] + carry;
            if (j < (int)b.size()) cur += a[i] * b[j];
            c[i + j] = cur % 10;
            carry = cur / 10;
        }
    }
    while (c.size() > 1 && c.back() == 0) c.pop_back();
    return c;
}

BigInt div(const BigInt& a, const BigInt& b) {
    if (lessThan(a, b)) return BigInt(1, 0);
    int n = a.size();
    int m = b.size();
    int shift = n - m;
    
    BigInt rem = a;
    BigInt q(shift + 1, 0);
    
    for (int i = shift; i >= 0; i--) {
        BigInt divisor;
        for (int k = 0; k < i; k++) divisor.push_back(0);
        for (int j = 0; j < m; j++) divisor.push_back(b[j]);
        
        int cnt = 0;
        while (!lessThan(rem, divisor)) {
            rem = sub(rem, divisor);
            cnt++;
        }
        q[i] = cnt;
    }
    
    while (q.size() > 1 && q.back() == 0) q.pop_back();
    return q;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    string a, op, b;
    while (cin >> a >> op >> b) {
        BigInt A = fromStr(a);
        BigInt B = fromStr(b);
        BigInt result;
        bool neg = false;
        
        if (op == "+") {
            result = add(A, B);
        } else if (op == "-") {
            if (lessThan(A, B)) {
                result = sub(B, A);
                neg = true;
            } else {
                result = sub(A, B);
            }
        } else if (op == "*") {
            result = mul(A, B);
        } else if (op == "/") {
            result = div(A, B);
        }
        
        string s = toStr(result);
        if (neg && s != "0") cout << "-";
        cout << s << "\n";
    }
    return 0;
}
