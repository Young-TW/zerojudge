#include <cstdio>
#include <vector>

struct BigInt {
    std::vector<int> digits;
    
    BigInt() {}
    
    BigInt(int x) {
        if (x > 0) digits.push_back(x);
    }
    
    void add(const BigInt& other) {
        int carry = 0;
        for (size_t i = 0; i < digits.size() || i < other.digits.size() || carry; ++i) {
            if (i == digits.size()) digits.push_back(0);
            int sum = digits[i] + carry;
            if (i < other.digits.size()) sum += other.digits[i];
            digits[i] = sum % 100000000;
            carry = sum / 100000000;
        }
    }
    
    void print() const {
        if (digits.empty()) {
            printf("0\n");
            return;
        }
        printf("%d", digits.back());
        for (int i = (int)digits.size() - 2; i >= 0; --i) {
            printf("%08d", digits[i]);
        }
        printf("\n");
    }
};

const int MAX_N = 10000;
BigInt f[MAX_N + 1];
BigInt pow2[500];

void precompute() {
    pow2[0] = BigInt(1);
    for (int i = 1; i < 500; ++i) {
        pow2[i] = pow2[i - 1];
        pow2[i].add(pow2[i - 1]);
    }
    
    f[0] = BigInt(0);
    int n = 1;
    for (int m = 1; n <= MAX_N; ++m) {
        for (int i = 0; i < m && n <= MAX_N; ++i, ++n) {
            f[n] = f[n - 1];
            f[n].add(pow2[m - 1]);
        }
    }
}

int main() {
    precompute();
    int n;
    while (scanf("%d", &n) == 1) {
        f[n].print();
    }
    return 0;
}
