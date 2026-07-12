#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <utility>

using namespace std;

string add(string a, string b) {
    if (a.length() < b.length()) swap(a, b);
    string res = "";
    int carry = 0;
    int la = a.length(), lb = b.length();
    for (int i = 0; i < lb; ++i) {
        int sum = (a[la - 1 - i] - '0') + (b[lb - 1 - i] - '0') + carry;
        res += char('0' + sum % 10);
        carry = sum / 10;
    }
    for (int i = lb; i < la; ++i) {
        int sum = (a[la - 1 - i] - '0') + carry;
        res += char('0' + sum % 10);
        carry = sum / 10;
    }
    if (carry) res += char('0' + carry);
    reverse(res.begin(), res.end());
    size_t start = res.find_first_not_of('0');
    if (start == string::npos) return "0";
    return res.substr(start);
}

string subtract(string a, string b) {
    string res = "";
    int la = a.length(), lb = b.length();
    int carry = 0;
    for (int i = 0; i < lb; ++i) {
        int diff = (a[la - 1 - i] - '0') - (b[lb - 1 - i] - '0') - carry;
        if (diff < 0) {
            diff += 10;
            carry = 1;
        } else {
            carry = 0;
        }
        res += char('0' + diff);
    }
    for (int i = lb; i < la; ++i) {
        int diff = (a[la - 1 - i] - '0') - carry;
        if (diff < 0) {
            diff += 10;
            carry = 1;
        } else {
            carry = 0;
        }
        res += char('0' + diff);
    }
    reverse(res.begin(), res.end());
    size_t start = res.find_first_not_of('0');
    if (start == string::npos) return "0";
    return res.substr(start);
}

string multiply(string a, string b) {
    if (a == "0" || b == "0") return "0";
    int la = a.length(), lb = b.length();
    vector<int> res(la + lb, 0);
    for (int i = la - 1; i >= 0; --i) {
        for (int j = lb - 1; j >= 0; --j) {
            res[i + j + 1] += (a[i] - '0') * (b[j] - '0');
        }
    }
    for (int i = la + lb - 1; i > 0; --i) {
        res[i - 1] += res[i] / 10;
        res[i] %= 10;
    }
    string result = "";
    for (int i = 0; i < la + lb; ++i) {
        if (res[i] == 0 && result.empty()) continue;
        result += char('0' + res[i]);
    }
    return result.empty() ? "0" : result;
}

int compare(const string& a, const string& b) {
    if (a.length() != b.length()) {
        return a.length() < b.length() ? -1 : 1;
    }
    return a.compare(b);
}

string sqrt_str(string s) {
    if (s.length() % 2 != 0) {
        s = "0" + s;
    }
    string res = "0";
    string rem = "0";
    for (size_t i = 0; i < s.length(); i += 2) {
        rem = multiply(rem, "100");
        rem = add(rem, s.substr(i, 2));
        
        string res20 = multiply(res, "20");
        int d = 0;
        string final_product = "0";
        for (int trial = 9; trial >= 0; --trial) {
            string trial_str = to_string(trial);
            string factor = add(res20, trial_str);
            string product = multiply(factor, trial_str);
            if (compare(product, rem) <= 0) {
                d = trial;
                final_product = product;
                break;
            }
        }
        res = multiply(res, "10");
        res = add(res, to_string(d));
        rem = subtract(rem, final_product);
    }
    return res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    string n_str;
    while (cin >> n_str) {
        string num = n_str + string(100, '0');
        string res = sqrt_str(num);
        while (res.length() < 51) {
            res = "0" + res;
        }
        string int_part = res.substr(0, res.length() - 50);
        string frac_part = res.substr(res.length() - 50);
        cout << int_part << "." << frac_part << "\n";
    }
    return 0;
}
