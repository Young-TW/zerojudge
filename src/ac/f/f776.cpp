#include <iostream>
#include <string>
#include <vector>
#include <cstdint>
#include <algorithm>
#include <cstdlib>

using namespace std;

class BigInt {
public:
    vector<uint32_t> digits;
    static const uint32_t BASE = 1000000000;

    BigInt() {}
    BigInt(uint64_t val) {
        while (val) {
            digits.push_back(val % BASE);
            val /= BASE;
        }
    }
    BigInt(const string& s) {
        if (s == "0") return;
        for (int i = s.size()-1; i >= 0; i -= 9) {
            int start = max(0, i - 9 + 1);
            int len = i - start + 1;
            string sub = s.substr(start, len);
            uint32_t val = stoul(sub);
            digits.push_back(val);
        }
        trim();
    }

    bool is_zero() const { return digits.empty(); }
    void trim() {
        while (!digits.empty() && digits.back() == 0) digits.pop_back();
    }
    string to_string() const {
        if (is_zero()) return "0";
        string s;
        for (int i = digits.size()-1; i >= 0; --i) {
            string part = std::to_string(digits[i]);
            if (i != digits.size()-1) {
                part = string(9 - part.size(), '0') + part;
            }
            s += part;
        }
        return s;
    }
};

bool operator<(const BigInt& a, const BigInt& b) {
    if (a.digits.size() != b.digits.size())
        return a.digits.size() < b.digits.size();
    for (int i = a.digits.size()-1; i >= 0; --i) {
        if (a.digits[i] != b.digits[i])
            return a.digits[i] < b.digits[i];
    }
    return false;
}
bool operator==(const BigInt& a, const BigInt& b) {
    return a.digits == b.digits;
}
bool operator!=(const BigInt& a, const BigInt& b) { return !(a == b); }
bool operator<=(const BigInt& a, const BigInt& b) { return !(b < a); }
bool operator>(const BigInt& a, const BigInt& b) { return b < a; }
bool operator>=(const BigInt& a, const BigInt& b) { return !(a < b); }

BigInt operator+(const BigInt& a, const BigInt& b) {
    BigInt res;
    int carry = 0;
    size_t max_len = max(a.digits.size(), b.digits.size());
    for (size_t i = 0; i < max_len || carry; ++i) {
        uint64_t sum = carry;
        if (i < a.digits.size()) sum += a.digits[i];
        if (i < b.digits.size()) sum += b.digits[i];
        carry = sum / BigInt::BASE;
        res.digits.push_back(sum % BigInt::BASE);
    }
    res.trim();
    return res;
}

BigInt operator-(const BigInt& a, const BigInt& b) {
    BigInt res;
    int borrow = 0;
    for (size_t i = 0; i < a.digits.size(); ++i) {
        int64_t diff = a.digits[i] - borrow;
        if (i < b.digits.size()) diff -= b.digits[i];
        if (diff < 0) {
            diff += BigInt::BASE;
            borrow = 1;
        } else {
            borrow = 0;
        }
        res.digits.push_back(diff);
    }
    res.trim();
    return res;
}

BigInt operator*(const BigInt& a, const BigInt& b) {
    if (a.is_zero() || b.is_zero()) return BigInt(0);
    vector<uint64_t> res(a.digits.size() + b.digits.size(), 0);
    for (size_t i = 0; i < a.digits.size(); ++i) {
        uint64_t ai = a.digits[i];
        for (size_t j = 0; j < b.digits.size(); ++j) {
            res[i+j] += ai * b.digits[j];
        }
    }
    uint64_t carry = 0;
    BigInt ans;
    for (size_t i = 0; i < res.size(); ++i) {
        uint64_t val = res[i] + carry;
        carry = val / BigInt::BASE;
        ans.digits.push_back(val % BigInt::BASE);
    }
    while (carry) {
        ans.digits.push_back(carry % BigInt::BASE);
        carry /= BigInt::BASE;
    }
    ans.trim();
    return ans;
}

BigInt operator/(const BigInt& a, int divisor) {
    if (a.is_zero()) return BigInt(0);
    vector<uint32_t> q;
    uint64_t rem = 0;
    for (int i = a.digits.size()-1; i >= 0; --i) {
        rem = rem * BigInt::BASE + a.digits[i];
        uint64_t q_digit = rem / divisor;
        rem %= divisor;
        if (!q.empty() || q_digit != 0) {
            q.push_back(q_digit);
        }
    }
    if (q.empty()) return BigInt(0);
    reverse(q.begin(), q.end());
    BigInt res;
    res.digits = q;
    return res;
}

BigInt sum_1_to_n(const BigInt& n) {
    if (n.is_zero()) return BigInt(0);
    BigInt one(1);
    return n * (n + one) / 2;
}

BigInt sum_squares(const BigInt& n) {
    if (n.is_zero()) return BigInt(0);
    BigInt one(1);
    BigInt two(2);
    BigInt n_plus_1 = n + one;
    BigInt two_n_plus_1 = two * n + one;
    return n * n_plus_1 * two_n_plus_1 / 6;
}

BigInt range_sum(const BigInt& L, const BigInt& R) {
    if (L > R) return BigInt(0);
    BigInt sum_R = sum_1_to_n(R);
    BigInt L_minus_1 = L - BigInt(1);
    BigInt sum_Lm1 = sum_1_to_n(L_minus_1);
    return sum_R - sum_Lm1;
}

BigInt range_sum_squares(const BigInt& L, const BigInt& R) {
    if (L > R) return BigInt(0);
    BigInt sum_R = sum_squares(R);
    BigInt L_minus_1 = L - BigInt(1);
    BigInt sum_Lm1 = sum_squares(L_minus_1);
    return sum_R - sum_Lm1;
}

BigInt min(const BigInt& a, const BigInt& b) { return a < b ? a : b; }
BigInt max(const BigInt& a, const BigInt& b) { return a < b ? b : a; }

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    string N_str;
    while (cin >> N_str) {
        long long T;
        cin >> T;
        while (T--) {
            string x1_str, y1_str, x2_str, y2_str;
            cin >> x1_str >> y1_str >> x2_str >> y2_str;
            BigInt a(x1_str), b(x2_str), c(y1_str), d(y2_str);

            BigInt S_y = range_sum(c, d);
            BigInt cnt_y = (d - c) + BigInt(1);

            BigInt S1(0);
            BigInt c_minus_1 = c - BigInt(1);
            BigInt R1 = min(b, c_minus_1);
            if (a <= R1) {
                BigInt cnt1 = (R1 - a) + BigInt(1);
                S1 = cnt1 * S_y;
            }

            BigInt S2(0);
            BigInt d_plus_1 = d + BigInt(1);
            BigInt L2 = max(a, d_plus_1);
            if (L2 <= b) {
                BigInt sum_x2 = range_sum(L2, b);
                S2 = cnt_y * sum_x2;
            }

            BigInt S3(0);
            BigInt L3 = max(a, c);
            BigInt R3 = min(b, d);
            if (L3 <= R3) {
                BigInt cnt3 = (R3 - L3) + BigInt(1);
                BigInt sum_x3 = range_sum(L3, R3);
                BigInt sum_sq3 = range_sum_squares(L3, R3);

                BigInt tempA = sum_sq3 + sum_x3;
                BigInt c_sum_x3 = c * sum_x3;
                BigInt A = tempA - c_sum_x3;

                BigInt S_d = sum_1_to_n(d);
                BigInt term1 = BigInt(2) * cnt3 * S_d;
                BigInt term2 = sum_sq3 + sum_x3;
                BigInt diff = term1 - term2;
                BigInt B = diff / 2;

                S3 = A + B;
            }

            BigInt total = S1 + S2 + S3;
            cout << total.to_string() << '\n';
        }
    }
    return 0;
}
