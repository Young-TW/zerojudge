#include <iostream>
#include <vector>
#include <cstdint>
#include <iomanip>

using namespace std;

const uint32_t BASE = 1000000000;
vector<vector<uint32_t>> pow3_cache;

void ensure_cache(int max_n) {
    if (pow3_cache.empty()) {
        pow3_cache.push_back({1});
    }
    for (int i = pow3_cache.size(); i <= max_n + 1; ++i) {
        vector<uint32_t> curr = pow3_cache[i-1];
        uint64_t carry = 0;
        for (size_t j = 0; j < curr.size(); ++j) {
            uint64_t val = (uint64_t)curr[j] * 3 + carry;
            curr[j] = val % BASE;
            carry = val / BASE;
        }
        while (carry) {
            curr.push_back(carry % BASE);
            carry /= BASE;
        }
        pow3_cache.push_back(curr);
    }
}

void add_1(vector<uint32_t>& num) {
    uint64_t carry = 1;
    for (size_t i = 0; i < num.size() && carry; ++i) {
        uint64_t val = (uint64_t)num[i] + carry;
        num[i] = val % BASE;
        carry = val / BASE;
    }
    if (carry) {
        num.push_back(carry);
    }
}

void divide_by_2(vector<uint32_t>& num) {
    uint64_t rem = 0;
    for (int i = num.size() - 1; i >= 0; --i) {
        uint64_t val = rem * BASE + num[i];
        num[i] = val / 2;
        rem = val % 2;
    }
    while (num.size() > 1 && num.back() == 0) {
        num.pop_back();
    }
}

void print_num(const vector<uint32_t>& num) {
    if (num.empty()) {
        cout << 0;
        return;
    }
    cout << num.back();
    for (int i = num.size() - 2; i >= 0; --i) {
        cout << setfill('0') << setw(9) << num[i];
    }
}

void solve() {
    int n;
    while (cin >> n) {
        if (n == 0) {
            cout << 1 << "\n";
            continue;
        }
        ensure_cache(n);
        vector<uint32_t> res = pow3_cache[n+1];
        add_1(res);
        divide_by_2(res);
        print_num(res);
        cout << "\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
