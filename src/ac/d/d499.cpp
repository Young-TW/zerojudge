#include <iostream>
#include <vector>
#include <cstdint>
#include <algorithm>

using namespace std;

const uint32_t BASE = 1000000000;

vector<uint32_t> multiply(const vector<uint32_t>& a, const vector<uint32_t>& b) {
    if (a.empty() || b.empty()) return {0};
    
    vector<uint64_t> temp(a.size() + b.size(), 0);
    
    for (size_t i = 0; i < a.size(); ++i) {
        if (a[i] == 0) continue;
        uint64_t carry = 0;
        for (size_t j = 0; j < b.size(); ++j) {
            uint64_t cur = temp[i + j] + (uint64_t)a[i] * b[j] + carry;
            temp[i + j] = cur % BASE;
            carry = cur / BASE;
        }
        if (carry > 0) {
            temp[i + b.size()] += carry;
        }
    }
    
    vector<uint32_t> res(temp.size());
    for (size_t i = 0; i < temp.size(); ++i) {
        res[i] = (uint32_t)temp[i];
    }
    
    while (res.size() > 1 && res.back() == 0) {
        res.pop_back();
    }
    return res;
}

void print_num(const vector<uint32_t>& num) {
    cout << num.back();
    if (num.size() > 1) {
        for (size_t i = num.size() - 2; i < num.size(); --i) {
            cout.width(9);
            cout.fill('0');
            cout << num[i];
        }
    }
    cout << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    long long a;
    long long n;
    
    while (cin >> a >> n) {
        if (n == 0) {
            cout << "1\n";
            continue;
        }
        
        vector<uint32_t> result = {1};
        vector<uint32_t> base;
        
        if (a == 0) {
            base = {0};
        } else if (a < 0) {
            uint64_t abs_a = (uint64_t)(-(a + 1)) + 1;
            while (abs_a > 0) {
                base.push_back((uint32_t)(abs_a % BASE));
                abs_a /= BASE;
            }
            if (n % 2 != 0) {
                cout << "-";
            }
        } else {
            uint64_t u_a = (uint64_t)a;
            while (u_a > 0) {
                base.push_back((uint32_t)(u_a % BASE));
                u_a /= BASE;
            }
        }
        
        long long p = n;
        while (p > 0) {
            if (p & 1) {
                result = multiply(result, base);
            }
            p >>= 1;
            if (p > 0) {
                base = multiply(base, base);
            }
        }
        
        print_num(result);
    }
    
    return 0;
}
