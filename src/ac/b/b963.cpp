#include <iostream>
#include <string>

using namespace std;

long long toDecimal(const string& s, int base) {
    long long res = 0;
    for (size_t i = 0; i < s.size(); ++i) {
        char c = s[i];
        int val;
        if (c >= '0' && c <= '9') {
            val = c - '0';
        } else if (c >= 'A' && c <= 'Z') {
            val = c - 'A' + 10;
        } else if (c >= 'a' && c <= 'z') {
            val = c - 'a' + 10;
        }
        res = res * base + val;
    }
    return res;
}

string toBase(long long num, int base) {
    if (num == 0) return "0";
    string res = "";
    while (num > 0) {
        int val = num % base;
        char c;
        if (val < 10) {
            c = val + '0';
        } else {
            c = val - 10 + 'A';
        }
        res = c + res;
        num /= base;
    }
    return res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n1, n2, m;
    string s1, s2;
    while (cin >> n1 >> s1 >> n2 >> s2 >> m) {
        long long val1 = toDecimal(s1, n1);
        long long val2 = toDecimal(s2, n2);
        long long sum = val1 + val2;
        cout << toBase(sum, m) << "\n";
    }
    return 0;
}
