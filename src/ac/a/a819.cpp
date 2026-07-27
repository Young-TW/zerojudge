#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;
using int128 = __int128;

struct Fraction {
    int128 num;
    int128 den;

    Fraction() : num(0), den(1) {}
    Fraction(int128 n) : num(n), den(1) {}
    Fraction(int128 n, int128 d) : num(n), den(d) {}

    void reduce() {
        if (den < 0) {
            num = -num;
            den = -den;
        }
        if (den == 0) return;
        int128 a = num, b = den;
        if (a < 0) a = -a;
        if (b < 0) b = -b;
        while (b > 0) {
            int128 temp = a % b;
            a = b;
            b = temp;
        }
        if (a > 0) {
            num /= a;
            den /= a;
        }
    }

    bool operator==(const Fraction& other) const {
        return num == other.num && den == other.den;
    }
};

Fraction operator+(const Fraction& a, const Fraction& b) {
    Fraction res(a.num * b.den + b.num * a.den, a.den * b.den);
    res.reduce();
    return res;
}

Fraction operator-(const Fraction& a, const Fraction& b) {
    Fraction res(a.num * b.den - b.num * a.den, a.den * b.den);
    res.reduce();
    return res;
}

Fraction operator*(const Fraction& a, const Fraction& b) {
    Fraction res(a.num * b.num, a.den * b.den);
    res.reduce();
    return res;
}

Fraction operator/(const Fraction& a, const Fraction& b) {
    Fraction res(a.num * b.den, a.den * b.num);
    res.reduce();
    return res;
}

bool apply(const Fraction& a, char op, const Fraction& b, Fraction& res) {
    if (op == '+') res = a + b;
    else if (op == '-') res = a - b;
    else if (op == '*') res = a * b;
    else if (op == '/') {
        if (b.num == 0) return false;
        res = a / b;
    } else return false;
    return true;
}

bool compute(const vector<Fraction>& nums, const vector<char>& ops, Fraction& result) {
    if (ops.empty()) {
        result = nums[0];
        return true;
    }
    if (ops.size() == 1) {
        return apply(nums[0], ops[0], nums[1], result);
    }
    char op1 = ops[0], op2 = ops[1];
    int prec1 = (op1 == '+' || op1 == '-') ? 1 : 2;
    int prec2 = (op2 == '+' || op2 == '-') ? 1 : 2;
    if (prec1 >= prec2) {
        Fraction mid;
        if (!apply(nums[0], op1, nums[1], mid)) return false;
        return apply(mid, op2, nums[2], result);
    } else {
        Fraction mid;
        if (!apply(nums[1], op2, nums[2], mid)) return false;
        return apply(nums[0], op1, mid, result);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    while (cin >> n) {
        string s;
        long long target_ll;
        if (!(cin >> s >> target_ll)) break;
        
        Fraction target(target_ll, 1);
        
        if (s.length() == (size_t)n) {
            long long val = stoll(s);
            Fraction f(val, 1);
            if (f == target) {
                cout << s << "\n";
            }
        }
        
        for (int i = 1; i < n; ++i) {
            string left_str = s.substr(0, i);
            string right_str = s.substr(i);
            long long left = stoll(left_str);
            long long right = stoll(right_str);
            Fraction f_left(left, 1);
            Fraction f_right(right, 1);
            for (char op : {'+', '-', '*', '/'}) {
                Fraction res;
                if (apply(f_left, op, f_right, res)) {
                    if (res == target) {
                        cout << left_str << op << right_str << "\n";
                    }
                }
            }
        }
        
        for (int i = 1; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                string left_str = s.substr(0, i);
                string mid_str = s.substr(i, j - i);
                string right_str = s.substr(j);
                long long left = stoll(left_str);
                long long mid = stoll(mid_str);
                long long right = stoll(right_str);
                Fraction f_left(left, 1);
                Fraction f_mid(mid, 1);
                Fraction f_right(right, 1);
                for (char op1 : {'+', '-', '*', '/'}) {
                    for (char op2 : {'+', '-', '*', '/'}) {
                        vector<Fraction> nums = {f_left, f_mid, f_right};
                        vector<char> ops = {op1, op2};
                        Fraction res;
                        if (compute(nums, ops, res)) {
                            if (res == target) {
                                cout << left_str << op1 << mid_str << op2 << right_str << "\n";
                            }
                        }
                    }
                }
            }
        }
    }
    return 0;
}
