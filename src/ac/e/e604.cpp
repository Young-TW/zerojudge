#include <bits/stdc++.h>
using namespace std;

const uint32_t BASE = 1000000000U;          // 10^9

// multiply big integer by a small uint32_t (m = 2 or 3)
void mul_small(vector<uint32_t> &a, uint32_t m) {
    uint64_t carry = 0;
    for (size_t i = 0; i < a.size(); ++i) {
        uint64_t cur = (uint64_t)a[i] * m + carry;
        a[i] = (uint32_t)(cur % BASE);
        carry = cur / BASE;
    }
    while (carry) {
        a.push_back((uint32_t)(carry % BASE));
        carry /= BASE;
    }
}

// subtract a small uint32_t (s = 1) ; assumes a >= s
void sub_small(vector<uint32_t> &a, uint32_t s) {
    uint64_t borrow = s;
    for (size_t i = 0; i < a.size() && borrow; ++i) {
        uint64_t cur = (uint64_t)a[i];
        if (cur >= borrow) {
            a[i] = (uint32_t)(cur - borrow);
            borrow = 0;
        } else {
            a[i] = (uint32_t)(cur + BASE - borrow);
            borrow = 1;
        }
    }
    while (a.size() > 1 && a.back() == 0) a.pop_back();
}

// output big integer
void print_big(const vector<uint32_t> &a) {
    int n = (int)a.size();
    cout << a.back();
    for (int i = n - 2; i >= 0; --i)
        cout << setw(9) << setfill('0') << a[i];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    while (cin >> n) {
        if (n == 0) {
            cout << 1 << '\n';
            continue;
        }
        vector<uint32_t> num(1, 1);          // start with 1
        for (int i = 0; i < n; ++i)          // compute 3^n
            mul_small(num, 3);
        mul_small(num, 2);                   // 2 * 3^n
        sub_small(num, 1);                   // -1
        print_big(num);
        cout << '\n';
    }
    return 0;
}
