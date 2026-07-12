#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

struct Big {
    vector<int> d;
    Big() {}
    Big(long long x) {
        if (x == 0) { d.push_back(0); return; }
        while (x > 0) { d.push_back((int)(x % 10)); x /= 10; }
    }
    Big(const string& s) {
        for (int i = (int)s.size() - 1; i >= 0; i--) d.push_back(s[i] - '0');
    }
    Big operator+(const Big& o) const {
        Big r;
        int carry = 0;
        size_t n = max(d.size(), o.d.size());
        for (size_t i = 0; i < n || carry; i++) {
            int sum = carry;
            if (i < d.size()) sum += d[i];
            if (i < o.d.size()) sum += o.d[i];
            r.d.push_back(sum % 10);
            carry = sum / 10;
        }
        return r;
    }
    bool operator>=(const Big& o) const {
        if (d.size() != o.d.size()) return d.size() > o.d.size();
        for (int i = (int)d.size() - 1; i >= 0; i--) {
            if (d[i] != o.d[i]) return d[i] > o.d[i];
        }
        return true;
    }
    string toString() const {
        string s;
        for (int i = (int)d.size() - 1; i >= 0; i--) s += (char)('0' + d[i]);
        return s;
    }
    long long digitSum() const {
        long long s = 0;
        for (size_t i = 0; i < d.size(); i++) s += d[i];
        return s;
    }
};

int main() {
    vector<Big> fib(601);
    fib[1] = Big(1LL);
    fib[2] = Big(1LL);
    for (int i = 3; i <= 600; i++) {
        fib[i] = fib[i-1] + fib[i-2];
    }
    Big threshold("10000000000000000000");
    int n;
    while (cin >> n && n != 0) {
        Big harvest = fib[5 * n];
        cout << harvest.toString() << "\n";
        if (harvest >= threshold) {
            long long ds = harvest.digitSum();
            long long days = ds / (2LL * n);
            cout << days << "\n";
        } else {
            cout << 0 << "\n";
        }
    }
    return 0;
}
