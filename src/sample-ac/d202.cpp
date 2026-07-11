#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    string s1, s2;
    while (cin >> s1 >> s2) {
        size_t dot1 = s1.find('.');
        size_t dot2 = s2.find('.');
        
        string int1, frac1, int2, frac2;
        if (dot1 == string::npos) {
            int1 = s1;
            frac1 = "";
        } else {
            int1 = s1.substr(0, dot1);
            frac1 = s1.substr(dot1 + 1);
        }
        if (dot2 == string::npos) {
            int2 = s2;
            frac2 = "";
        } else {
            int2 = s2.substr(0, dot2);
            frac2 = s2.substr(dot2 + 1);
        }
        
        size_t max_frac_len = max(frac1.length(), frac2.length());
        if (max_frac_len < 205) max_frac_len = 205;
        
        if (frac1.length() < max_frac_len) frac1.append(max_frac_len - frac1.length(), '0');
        if (frac2.length() < max_frac_len) frac2.append(max_frac_len - frac2.length(), '0');
        
        size_t max_int_len = max(int1.length(), int2.length());
        if (int1.length() < max_int_len) int1 = string(max_int_len - int1.length(), '0') + int1;
        if (int2.length() < max_int_len) int2 = string(max_int_len - int2.length(), '0') + int2;
        
        string num1 = int1 + frac1;
        string num2 = int2 + frac2;
        
        string sum(num1.length() + 1, '0');
        int carry = 0;
        int len = num1.length();
        for (int i = len - 1; i >= 0; --i) {
            int d1 = num1[i] - '0';
            int d2 = num2[i] - '0';
            int s = d1 + d2 + carry;
            carry = s / 10;
            sum[i + 1] = (s % 10) + '0';
        }
        sum[0] = carry + '0';
        
        size_t first_non_zero = sum.find_first_not_of('0');
        if (first_non_zero == string::npos) {
            sum = "0";
        } else {
            sum = sum.substr(first_non_zero);
        }
        
        size_t total_len = max_int_len + max_frac_len;
        if (sum.length() < total_len) {
            sum = string(total_len - sum.length(), '0') + sum;
        }
        
        int idx_201 = (int)sum.length() - (int)max_frac_len + 200;
        if (sum[idx_201] >= '5') {
            int idx_200 = idx_201 - 1;
            carry = 1;
            for (int i = idx_200; i >= 0; --i) {
                int d = sum[i] - '0' + carry;
                if (d >= 10) {
                    sum[i] = '0';
                    carry = 1;
                } else {
                    sum[i] = d + '0';
                    carry = 0;
                    break;
                }
            }
            if (carry) {
                sum = "1" + sum;
            }
        }
        
        size_t L = sum.length();
        string result_int = sum.substr(0, L - max_frac_len);
        string result_frac = sum.substr(L - max_frac_len, 200);
        
        first_non_zero = result_int.find_first_not_of('0');
        if (first_non_zero == string::npos) {
            result_int = "0";
        } else {
            result_int = result_int.substr(first_non_zero);
        }
        
        cout << result_int << "." << result_frac << "\n";
    }
    return 0;
}
