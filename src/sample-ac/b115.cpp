#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

string removeLeadingZeros(string s) {
    int pos = 0;
    while (pos < (int)s.size() - 1 && s[pos] == '0') {
        pos++;
    }
    return s.substr(pos);
}

int compare(const string& a, const string& b) {
    if (a.size() != b.size()) {
        return a.size() > b.size() ? 1 : -1;
    }
    return a.compare(b);
}

string sub(string a, const string& b) {
    string res = "";
    int i = a.size() - 1;
    int j = b.size() - 1;
    int borrow = 0;
    while (i >= 0 || j >= 0) {
        int da = i >= 0 ? a[i--] - '0' : 0;
        int db = j >= 0 ? b[j--] - '0' : 0;
        int diff = da - db - borrow;
        if (diff < 0) {
            diff += 10;
            borrow = 1;
        } else {
            borrow = 0;
        }
        res += (char)(diff + '0');
    }
    while (res.size() > 1 && res.back() == '0') {
        res.pop_back();
    }
    reverse(res.begin(), res.end());
    return res;
}

string mul(const string& a, const string& b) {
    int n = a.size();
    int m = b.size();
    vector<int> res(n + m, 0);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            res[i + j] += (a[n - 1 - i] - '0') * (b[m - 1 - j] - '0');
        }
    }
    for (int i = 0; i < n + m - 1; ++i) {
        res[i + 1] += res[i] / 10;
        res[i] %= 10;
    }
    while (res.size() > 1 && res.back() == 0) {
        res.pop_back();
    }
    string ans = "";
    for (int i = res.size() - 1; i >= 0; --i) {
        ans += (char)(res[i] + '0');
    }
    return ans;
}

string div(string a, string b) {
    string res = "";
    string cur = "";
    for (size_t i = 0; i < a.size(); ++i) {
        cur += a[i];
        int pos = 0;
        while (pos < (int)cur.size() - 1 && cur[pos] == '0') {
            pos++;
        }
        cur = cur.substr(pos);
        
        int cnt = 0;
        while (compare(cur, b) >= 0) {
            cur = sub(cur, b);
            cnt++;
        }
        res += (char)(cnt + '0');
    }
    int pos = 0;
    while (pos < (int)res.size() - 1 && res[pos] == '0') {
        pos++;
    }
    return res.substr(pos);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    string a, b;
    char op;
    while (cin >> a >> op >> b) {
        a = removeLeadingZeros(a);
        b = removeLeadingZeros(b);
        if (op == '*') {
            cout << mul(a, b) << "\n";
        } else if (op == '/') {
            cout << div(a, b) << "\n";
        }
    }
    return 0;
}
