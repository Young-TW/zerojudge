#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

struct BigInt {
    vector<int> v;
    static const int BASE = 1000000000;
    
    BigInt() {
        v.reserve(5);
    }
    BigInt(int x) {
        v.reserve(5);
        if (x > 0) v.push_back(x);
    }
    
    BigInt& operator+=(const BigInt& other) {
        int carry = 0;
        for (size_t i = 0; i < max(v.size(), other.v.size()) || carry; ++i) {
            if (i == v.size()) v.push_back(0);
            v[i] += carry + (i < other.v.size() ? other.v[i] : 0);
            carry = v[i] >= BASE;
            if (carry) v[i] -= BASE;
        }
        return *this;
    }
    
    string to_string() const {
        if (v.empty()) return "0";
        string res = std::to_string(v.back());
        for (int i = (int)v.size() - 2; i >= 0; --i) {
            string part = std::to_string(v[i]);
            res += string(9 - part.length(), '0') + part;
        }
        return res;
    }
};

BigInt dp[755];
string ans[755];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    dp[0] = BigInt(1);
    for (int j = 1; j <= 750; j += 2) {
        for (int i = j; i <= 750; ++i) {
            dp[i] += dp[i - j];
        }
    }

    for (int i = 0; i <= 750; ++i) {
        ans[i] = dp[i].to_string();
    }

    int M;
    bool first_block = true;
    while (cin >> M) {
        if (!first_block) {
            cout << "\n";
        }
        first_block = false;
        for (int i = 0; i < M; ++i) {
            int N;
            cin >> N;
            cout << ans[N] << "\n";
        }
    }

    return 0;
}
