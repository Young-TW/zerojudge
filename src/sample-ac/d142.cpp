#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

string multiply_by_digit(const string& num, int d) {
    if (d == 0) return "0";
    if (d == 1) return num;
    string res;
    int carry = 0;
    for (int i = num.size() - 1; i >= 0; --i) {
        int prod = (num[i] - '0') * d + carry;
        res.push_back('0' + prod % 10);
        carry = prod / 10;
    }
    while (carry) {
        res.push_back('0' + carry % 10);
        carry /= 10;
    }
    reverse(res.begin(), res.end());
    return res;
}

int compare(const string& a, const string& b) {
    if (a.size() != b.size()) return a.size() < b.size() ? -1 : 1;
    for (size_t i = 0; i < a.size(); ++i) {
        if (a[i] != b[i]) return a[i] < b[i] ? -1 : 1;
    }
    return 0;
}

string subtract(const string& a, const string& b) {
    // assumes a >= b
    string res;
    int borrow = 0;
    int i = a.size() - 1, j = b.size() - 1;
    while (i >= 0) {
        int diff = (a[i] - '0') - borrow - (j >= 0 ? b[j] - '0' : 0);
        if (diff < 0) {
            diff += 10;
            borrow = 1;
        } else {
            borrow = 0;
        }
        res.push_back('0' + diff);
        --i; --j;
    }
    while (res.size() > 1 && res.back() == '0') res.pop_back();
    reverse(res.begin(), res.end());
    return res;
}

string normalize(const string& s) {
    size_t pos = s.find_first_not_of('0');
    if (pos == string::npos) return "0";
    return s.substr(pos);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    for (int tc = 0; tc < T; ++tc) {
        string Y;
        cin >> Y;

        // Split Y into groups of two digits from right to left
        vector<string> groups;
        for (int i = Y.size(); i > 0; i -= 2) {
            int start = max(0, i - 2);
            groups.push_back(Y.substr(start, i - start));
        }
        reverse(groups.begin(), groups.end());

        string current_result = "0";
        string remainder = "0";

        // Process first group
        string rem = groups[0];
        int x = 0;
        for (int d = 9; d >= 0; --d) {
            string d_str(1, '0' + d);
            string prod = multiply_by_digit(d_str, d);
            if (compare(prod, rem) <= 0) {
                x = d;
                break;
            }
        }
        current_result = string(1, '0' + x);
        string prod = multiply_by_digit(current_result, x);
        remainder = subtract(rem, prod);

        // Process remaining groups
        for (size_t idx = 1; idx < groups.size(); ++idx) {
            string group = groups[idx];
            // Bring down the next group
            if (remainder == "0") remainder = group;
            else remainder += group;
            remainder = normalize(remainder);

            // Compute 20 * current_result
            string twenty_curr = multiply_by_digit(current_result, 2);
            if (twenty_curr != "0") twenty_curr += "0";
            else twenty_curr = "0";

            // Find the next digit x
            x = 0;
            for (int d = 9; d >= 0; --d) {
                string temp = twenty_curr;
                if (temp == "0") temp = string(1, '0' + d);
                else temp[temp.size() - 1] = '0' + d;
                string product = multiply_by_digit(temp, d);
                if (compare(product, remainder) <= 0) {
                    x = d;
                    break;
                }
            }

            // Update remainder and current_result
            string temp = twenty_curr;
            if (temp == "0") temp = string(1, '0' + x);
            else temp[temp.size() - 1] = '0' + x;
            string product = multiply_by_digit(temp, x);
            remainder = subtract(remainder, product);
            current_result += char('0' + x);
        }

        cout << current_result << "\n";
        if (tc != T - 1) cout << "\n";
    }
    return 0;
}
