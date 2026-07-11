#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cctype>
using namespace std;

const string digits = "0123456789abcdefghijklmnopqrstuvwxyz";

long long to_decimal(const string &s, int base) {
    long long num = 0;
    for (char c : s) {
        num = num * base + digits.find(c);
    }
    return num;
}

string from_decimal(long long num, int base) {
    if (num == 0) return "0";
    string s;
    while (num > 0) {
        s += digits[num % base];
        num /= base;
    }
    reverse(s.begin(), s.end());
    return s;
}

vector<int> bigint_to_vec(const string &s, int base) {
    vector<int> num;
    for (char c : s) {
        num.push_back(digits.find(c));
    }
    return num;
}

string vec_to_bigint(const vector<int> &num, int base) {
    string s;
    for (int d : num) {
        s += digits[d];
    }
    return s;
}

vector<int> bigint_convert_base(const vector<int> &num, int from_base, int to_base) {
    vector<int> res;
    vector<int> current = num;

    while (!current.empty()) {
        int remainder = 0;
        for (int &d : current) {
            int temp = d + remainder * from_base;
            d = temp / to_base;
            remainder = temp % to_base;
        }
        res.push_back(remainder);

        while (!current.empty() && current[0] == 0) {
            current.erase(current.begin());
        }
    }

    reverse(res.begin(), res.end());
    return res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    while (cin >> T) {
        for (int i = 0; i < T; ++i) {
            int d1, d2;
            cin >> d1 >> d2;
            string s;
            cin >> s;

            if (s.size() <= 18) {
                long long num = to_decimal(s, d1);
                string res = from_decimal(num, d2);
                cout << res << '\n';
            } else {
                vector<int> num = bigint_to_vec(s, d1);
                vector<int> res = bigint_convert_base(num, d1, d2);
                cout << vec_to_bigint(res, d2) << '\n';
            }
        }
    }

    return 0;
}
