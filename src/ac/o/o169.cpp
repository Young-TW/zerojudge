#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef vector<int> BigInt;

BigInt mul(const BigInt& a, int b) {
    BigInt res;
    long long carry = 0;
    for (size_t i = 0; i < a.size(); ++i) {
        carry += (long long)a[i] * b;
        res.push_back(carry % 10);
        carry /= 10;
    }
    while (carry) {
        res.push_back(carry % 10);
        carry /= 10;
    }
    if (res.empty()) res.push_back(0);
    return res;
}

BigInt add(const BigInt& a, const BigInt& b) {
    BigInt res;
    int carry = 0;
    for (size_t i = 0; i < max(a.size(), b.size()) || carry; ++i) {
        int sum = carry;
        if (i < a.size()) sum += a[i];
        if (i < b.size()) sum += b[i];
        res.push_back(sum % 10);
        carry = sum / 10;
    }
    if (res.empty()) res.push_back(0);
    return res;
}

void print(const BigInt& a) {
    for (int i = a.size() - 1; i >= 0; --i) {
        cout << a[i];
    }
    cout << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int N, A;
    while (cin >> N >> A) {
        BigInt ans = {0};
        BigInt A_pow = {1};
        for (int i = 1; i <= N; ++i) {
            A_pow = mul(A_pow, A);
            BigInt term = mul(A_pow, i);
            ans = add(ans, term);
        }
        print(ans);
    }
    return 0;
}
