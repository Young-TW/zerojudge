#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

string multiply(const string& a, const string& b) {
    if (a == "0" || b == "0") return "0";
    int n = a.size();
    int m = b.size();
    vector<int> res(n + m, 0);
    for (int i = n - 1; i >= 0; --i) {
        for (int j = m - 1; j >= 0; --j) {
            res[i + j + 1] += (a[i] - '0') * (b[j] - '0');
        }
    }
    for (int k = n + m - 1; k > 0; --k) {
        res[k - 1] += res[k] / 10;
        res[k] %= 10;
    }
    string str;
    if (res[0] >= 10) {
        str += to_string(res[0]);
    } else {
        if (res[0] != 0) str.push_back(res[0] + '0');
    }
    for (int i = 1; i < n + m; ++i) {
        str.push_back(res[i] + '0');
    }
    if (str.empty()) str = "0";
    return str;
}

string power(string base, int exp) {
    string res = "1";
    while (exp > 0) {
        if (exp % 2 == 1) res = multiply(res, base);
        base = multiply(base, base);
        exp /= 2;
    }
    return res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    string r_str;
    int n;
    while (cin >> r_str >> n) {
        string base = "";
        int d = 0;
        size_t dot_pos = r_str.find('.');
        if (dot_pos != string::npos) {
            d = r_str.length() - dot_pos - 1;
            for (char c : r_str) {
                if (c != '.') base += c;
            }
        } else {
            base = r_str;
        }
        
        size_t first_non_zero = base.find_first_not_of('0');
        if (first_non_zero != string::npos) {
            base = base.substr(first_non_zero);
        } else {
            base = "0";
        }
        
        string res_str = power(base, n);
        if (res_str == "0") {
            cout << "0\n";
            continue;
        }
        
        int D = d * n;
        if (res_str.length() <= D) {
            res_str = string(D - res_str.length(), '0') + res_str;
            res_str = "." + res_str;
        } else {
            res_str.insert(res_str.length() - D, ".");
        }
        
        if (res_str.find('.') != string::npos) {
            while (res_str.back() == '0') {
                res_str.pop_back();
            }
            if (res_str.back() == '.') {
                res_str.pop_back();
            }
        }
        
        if (res_str.find('.') != string::npos) {
            size_t dot_pos = res_str.find('.');
            bool all_zero = true;
            for (size_t i = 0; i < dot_pos; ++i) {
                if (res_str[i] != '0') {
                    all_zero = false;
                    break;
                }
            }
            if (all_zero) {
                res_str = res_str.substr(dot_pos);
            } else {
                size_t first_non_zero = res_str.find_first_not_of('0');
                if (first_non_zero != string::npos && first_non_zero < dot_pos) {
                    res_str = res_str.substr(first_non_zero);
                }
            }
        } else {
            size_t first_non_zero = res_str.find_first_not_of('0');
            if (first_non_zero != string::npos) {
                res_str = res_str.substr(first_non_zero);
            } else {
                res_str = "0";
            }
        }
        
        cout << res_str << "\n";
    }
    return 0;
}
