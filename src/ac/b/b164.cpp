#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>

struct BigInt {
    static const int BASE = 1000000000;
    std::vector<int> d;

    BigInt(long long v = 0) {
        if (v) d.push_back(static_cast<int>(v));
    }

    BigInt& operator+=(const BigInt& other) {
        int n = std::max(d.size(), other.d.size());
        d.resize(n, 0);
        long long carry = 0;
        for (int i = 0; i < n; ++i) {
            carry += d[i];
            if (i < (int)other.d.size()) carry += other.d[i];
            d[i] = static_cast<int>(carry % BASE);
            carry /= BASE;
        }
        while (carry) {
            d.push_back(static_cast<int>(carry % BASE));
            carry /= BASE;
        }
        return *this;
    }

    BigInt& operator*=(int m) {
        if (m == 0) {
            d.clear();
            return *this;
        }
        long long carry = 0;
        for (int i = 0; i < (int)d.size(); ++i) {
            carry += (long long)d[i] * m;
            d[i] = static_cast<int>(carry % BASE);
            carry /= BASE;
        }
        while (carry) {
            d.push_back(static_cast<int>(carry % BASE));
            carry /= BASE;
        }
        return *this;
    }

    bool operator<(const BigInt& other) const {
        if (d.size() != other.d.size()) return d.size() < other.d.size();
        for (int i = (int)d.size() - 1; i >= 0; --i) {
            if (d[i] != other.d[i]) return d[i] < other.d[i];
        }
        return false;
    }

    friend std::ostream& operator<<(std::ostream& os, const BigInt& x) {
        if (x.d.empty()) {
            os << 0;
            return os;
        }
        os << x.d.back();
        for (int i = (int)x.d.size() - 2; i >= 0; --i) {
            os << std::setw(9) << std::setfill('0') << x.d[i];
        }
        return os;
    }
};

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, m;
    bool firstCase = true;
    while (std::cin >> n >> m) {
        if (!firstCase) std::cout << "\n";
        firstCase = false;

        std::vector<std::vector<int>> matrix(n, std::vector<int>(m));
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                std::cin >> matrix[i][j];
            }
        }

        std::vector<BigInt> pow2(m + 1);
        pow2[0] = BigInt(1);
        for (int i = 1; i <= m; ++i) {
            pow2[i] = pow2[i - 1];
            pow2[i] *= 2;
        }

        BigInt total = 0;
        for (int row = 0; row < n; ++row) {
            const std::vector<int>& a = matrix[row];
            std::vector<std::vector<BigInt>> dp(m, std::vector<BigInt>(m));

            for (int len = 1; len <= m; ++len) {
                int step = m - len + 1;
                const BigInt& mult = pow2[step];
                for (int l = 0; l + len <= m; ++l) {
                    int r = l + len - 1;
                    if (len == 1) {
                        dp[l][r] = mult;
                        dp[l][r] *= a[l];
                    } else {
                        BigInt left = mult;
                        left *= a[l];
                        left += dp[l + 1][r];

                        BigInt right = mult;
                        right *= a[r];
                        right += dp[l][r - 1];

                        if (left < right) dp[l][r] = right;
                        else dp[l][r] = left;
                    }
                }
            }
            total += dp[0][m - 1];
        }

        std::cout << total << "\n";
    }
    return 0;
}
