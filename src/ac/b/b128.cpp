#include <iostream>
#include <vector>

using namespace std;

struct BigInt {
    vector<int> d;
    
    BigInt() {}
    BigInt(int x) {
        if (x == 0) d.push_back(0);
        while (x) {
            d.push_back(x % 10);
            x /= 10;
        }
    }

    BigInt(const BigInt& other) : d(other.d) {}

    void mul_add(int mul, int add) {
        long long carry = add;
        for (size_t i = 0; i < d.size(); ++i) {
            carry += (long long)d[i] * mul;
            d[i] = carry % 10;
            carry /= 10;
        }
        while (carry) {
            d.push_back(carry % 10);
            carry /= 10;
        }
    }

    void print() const {
        for (int i = d.size() - 1; i >= 0; --i) {
            cout << d[i];
        }
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    while (cin >> n) {
        BigInt A(1);
        for (int i = 1; i < n; ++i) {
            A.mul_add(i, 1);
        }
        BigInt S = A;
        S.mul_add(n * (n - 1), n);
        S.print();
        cout << "\n";
    }
    return 0;
}
