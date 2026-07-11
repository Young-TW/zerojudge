#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct BigInt {
    vector<int> d;
    
    BigInt() {}
    BigInt(long long x) {
        if (x == 0) d.push_back(0);
        while (x > 0) {
            d.push_back(x % 10);
            x /= 10;
        }
    }
    
    void trim() {
        while (d.size() > 1 && d.back() == 0) {
            d.pop_back();
        }
    }
    
    void multiply(int x) {
        long long carry = 0;
        for (size_t i = 0; i < d.size(); ++i) {
            long long prod = (long long)d[i] * x + carry;
            d[i] = prod % 10;
            carry = prod / 10;
        }
        while (carry > 0) {
            d.push_back(carry % 10);
            carry /= 10;
        }
    }
    
    BigInt divide(int x) const {
        BigInt q;
        q.d.resize(d.size());
        long long rem = 0;
        for (int i = d.size() - 1; i >= 0; --i) {
            long long cur = rem * 10 + d[i];
            q.d[i] = cur / x;
            rem = cur % x;
        }
        q.trim();
        return q;
    }
    
    bool operator<(const BigInt& other) const {
        if (d.size() != other.d.size()) {
            return d.size() < other.d.size();
        }
        for (int i = d.size() - 1; i >= 0; --i) {
            if (d[i] != other.d[i]) {
                return d[i] < other.d[i];
            }
        }
        return false;
    }
};

struct Minister {
    int a, b;
    bool operator<(const Minister& other) const {
        return (long long)a * b < (long long)other.a * other.b;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    while (cin >> n) {
        long long ka, kb;
        if (!(cin >> ka >> kb)) break;
        vector<Minister> m(n);
        for (int i = 0; i < n; ++i) {
            cin >> m[i].a >> m[i].b;
        }
        sort(m.begin(), m.end());
        
        BigInt S(ka);
        BigInt ans(0);
        
        for (int i = 0; i < n; ++i) {
            BigInt C = S.divide(m[i].b);
            if (ans < C) {
                ans = C;
            }
            S.multiply(m[i].a);
        }
        
        for (int i = ans.d.size() - 1; i >= 0; --i) {
            cout << ans.d[i];
        }
        cout << "\n";
    }
    return 0;
}
