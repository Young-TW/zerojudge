#include <bits/stdc++.h>
using namespace std;

/* ---------- utilities for decimal strings ---------- */
static int cmp(const string& a, const string& b) {
    if (a.size() != b.size()) return a.size() < b.size() ? -1 : 1;
    if (a == b) return 0;
    return a < b ? -1 : 1;
}
static string add(const string& a, const string& b) {
    string res;
    int i = (int)a.size() - 1, j = (int)b.size() - 1, carry = 0;
    while (i >= 0 || j >= 0 || carry) {
        int sum = carry;
        if (i >= 0) sum += a[i--] - '0';
        if (j >= 0) sum += b[j--] - '0';
        res.push_back(char('0' + (sum % 10)));
        carry = sum / 10;
    }
    reverse(res.begin(), res.end());
    return res;
}
static string sub(const string& a, const string& b) { // a >= b
    string res;
    int i = (int)a.size() - 1, j = (int)b.size() - 1, borrow = 0;
    while (i >= 0) {
        int diff = (a[i] - '0') - borrow - (j >= 0 ? (b[j] - '0') : 0);
        if (diff < 0) { diff += 10; borrow = 1; }
        else borrow = 0;
        res.push_back(char('0' + diff));
        --i; --j;
    }
    while (res.size() > 1 && res.back() == '0') res.pop_back();
    reverse(res.begin(), res.end());
    return res;
}
static string div2(const string& a) {
    string res;
    int carry = 0;
    for (char ch : a) {
        int cur = carry * 10 + (ch - '0');
        res.push_back(char('0' + cur / 2));
        carry = cur % 2;
    }
    size_t pos = res.find_first_not_of('0');
    if (pos == string::npos) return "0";
    return res.substr(pos);
}
static string mul(const string& a, const string& b) {
    if (a == "0" || b == "0") return "0";
    int n = a.size(), m = b.size();
    vector<int> prod(n + m, 0);
    for (int i = n - 1; i >= 0; --i) {
        for (int j = m - 1; j >= 0; --j) {
            int p = (a[i] - '0') * (b[j] - '0');
            int sum = prod[i + j + 1] + p;
            prod[i + j + 1] = sum % 10;
            prod[i + j] += sum / 10;
        }
    }
    string res;
    int i = 0;
    while (i < (int)prod.size() && prod[i] == 0) ++i;
    for (; i < (int)prod.size(); ++i) res.push_back(char('0' + prod[i]));
    return res.empty() ? "0" : res;
}

/* ---------- floor sqrt by binary search ---------- */
static string floorSqrt(const string& N) {
    if (N == "0" || N == "1") return N;
    int L = N.size();
    int k = (L + 1) / 2;
    string high = "1";
    high.append(k, '0');          // 10^k
    string low = "0";
    while (true) {
        // stop condition low+1 == high
        string lowPlus1 = add(low, "1");
        if (cmp(lowPlus1, high) == 0) break;
        // mid = (low + high) / 2
        string sum = add(low, high);
        string mid = div2(sum);
        string midsq = mul(mid, mid);
        if (cmp(midsq, N) <= 0) low = mid;
        else high = mid;
    }
    return low;
}

/* ---------- full‑width conversion ---------- */
static bool containsFullWidth(const string& s) {
    for (size_t i = 0; i + 1 < s.size(); ++i)
        if ((unsigned char)s[i] == 0xEF && (unsigned char)s[i+1] == 0xBC)
            return true;
    return false;
}
static string fullWidthToAscii(const string& s) {
    string out;
    for (size_t i = 0; i < s.size(); ) {
        unsigned char c = s[i];
        if (c == 0xEF && i + 2 < s.size() &&
            (unsigned char)s[i+1] == 0xBC) {
            unsigned char c3 = s[i+2];
            if (c3 >= 0x90 && c3 <= 0x99) {
                out.push_back('0' + (c3 - 0x90));
                i += 3;
                continue;
            }
        }
        if (c >= '0' && c <= '9') {
            out.push_back(c);
            ++i;
        } else {
            ++i; // ignore any other bytes
        }
    }
    // strip leading zeros, keep at least one digit
    size_t pos = out.find_first_not_of('0');
    if (pos == string::npos) return "0";
    return out.substr(pos);
}
static string asciiToFullWidth(const string& s) {
    string out;
    out.reserve(s.size() * 3);
    for (char ch : s) {
        unsigned char d = ch - '0';
        out.push_back(0xEF);
        out.push_back(0xBC);
        out.push_back(0x90 + d);
    }
    return out;
}

/* ---------- trim whitespace ---------- */
static string trim(const string& s) {
    size_t a = s.find_first_not_of(" \t\r\n");
    if (a == string::npos) return "";
    size_t b = s.find_last_not_of(" \t\r\n");
    return s.substr(a, b - a + 1);
}

/* ---------- main ---------- */
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    string line;
    while (getline(cin, line)) {
        line = trim(line);
        if (line.empty()) continue;
        string ascii = fullWidthToAscii(line);
        if (ascii == "0") break;
        string s = floorSqrt(ascii);
        string ans = mul(s, s);
        if (containsFullWidth(line))
            cout << asciiToFullWidth(ans) << '\n';
        else
            cout << ans << '\n';
    }
    return 0;
}
