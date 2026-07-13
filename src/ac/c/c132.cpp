#include <iostream>
#include <string>
#include <cctype>
#include <utility>

using namespace std;

string add(string s, int x) {
    int carry = x;
    for (int i = s.length() - 1; i >= 0 && carry; i--) {
        int sum = (s[i] - '0') + carry;
        s[i] = (sum % 10) + '0';
        carry = sum / 10;
    }
    while (carry) {
        s = (char)((carry % 10) + '0') + s;
        carry /= 10;
    }
    return s;
}

string sub(string s, int x) {
    int borrow = x;
    for (int i = s.length() - 1; i >= 0 && borrow; i--) {
        int diff = (s[i] - '0') - borrow;
        if (diff < 0) {
            diff += 10;
            borrow = 1;
        } else {
            borrow = 0;
        }
        s[i] = diff + '0';
    }
    int pos = 0;
    while (pos < s.length() - 1 && s[pos] == '0') pos++;
    return s.substr(pos);
}

string mul(string s, int x) {
    int carry = 0;
    for (int i = s.length() - 1; i >= 0; i--) {
        int prod = (s[i] - '0') * x + carry;
        s[i] = (prod % 10) + '0';
        carry = prod / 10;
    }
    while (carry) {
        s = (char)((carry % 10) + '0') + s;
        carry /= 10;
    }
    return s;
}

pair<string, int> divmod(string s, int x) {
    int rem = 0;
    string q = "";
    for (size_t i = 0; i < s.length(); i++) {
        int cur = rem * 10 + (s[i] - '0');
        q += (cur / x) + '0';
        rem = cur % x;
    }
    size_t pos = 0;
    while (pos < q.length() - 1 && q[pos] == '0') pos++;
    q = q.substr(pos);
    return make_pair(q, rem);
}

string formatNum(string num) {
    string res = "";
    size_t n = num.length();
    for (size_t i = 0; i < n; i++) {
        res += num[i];
        if ((n - i - 1) % 3 == 0 && i != n - 1) {
            res += ',';
        }
    }
    return res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    string input;
    while (cin >> input && input != "*") {
        string word, num;
        if (isdigit((unsigned char)input[0])) {
            num = input;
            word = "";
            string temp = num;
            while (temp != "0") {
                pair<string, int> res = divmod(temp, 26);
                temp = res.first;
                int rem = res.second;
                if (rem == 0) {
                    rem = 26;
                    temp = sub(temp, 1);
                }
                word = (char)('a' + rem - 1) + word;
            }
        } else {
            word = input;
            num = "0";
            for (size_t i = 0; i < word.length(); i++) {
                num = mul(num, 26);
                num = add(num, word[i] - 'a' + 1);
            }
        }
        cout << word;
        for (size_t i = word.length(); i < 22; i++) {
            cout << ' ';
        }
        cout << formatNum(num) << "\n";
    }
    return 0;
}
