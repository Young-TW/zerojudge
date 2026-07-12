#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <cstdio>

using namespace std;

const int BASE = 1000000000;

vector<int> multiply(const vector<int>& a, const vector<int>& b) {
    vector<int> res(a.size() + b.size(), 0);
    for (size_t i = 0; i < a.size(); ++i) {
        long long carry = 0;
        for (size_t j = 0; j < b.size(); ++j) {
            long long cur = (long long)res[i + j] + (long long)a[i] * b[j] + carry;
            res[i + j] = (int)(cur % BASE);
            carry = cur / BASE;
        }
        size_t pos = i + b.size();
        while (carry) {
            long long cur = (long long)res[pos] + carry;
            res[pos] = (int)(cur % BASE);
            carry = cur / BASE;
            ++pos;
        }
    }
    while (res.size() > 1 && res.back() == 0) {
        res.pop_back();
    }
    return res;
}

vector<int> power(int a, int n) {
    vector<int> result = {1};
    vector<int> base = {a};
    while (n > 0) {
        if (n & 1) {
            result = multiply(result, base);
        }
        base = multiply(base, base);
        n >>= 1;
    }
    return result;
}

string toString(const vector<int>& num) {
    if (num.empty()) return "0";
    stringstream ss;
    ss << num.back();
    char buf[16];
    for (int i = (int)num.size() - 2; i >= 0; --i) {
        snprintf(buf, sizeof(buf), "%09d", num[i]);
        ss << buf;
    }
    return ss.str();
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int a, n, i, k;
    while (cin >> a >> n >> i >> k) {
        vector<int> result = power(a, n);
        string s = toString(result);
        int len = s.length();
        int start = i - 1;
        string output;
        if (start >= len) {
            output = "";
        } else {
            int end = min(start + k, len);
            output = s.substr(start, end - start);
        }
        cout << "    " << output << '\n';
    }
    return 0;
}
