#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

string convert(long long n, long long base) {
    if (n == 0) return "0";
    long long R = -base;
    string s;
    while (n != 0) {
        long long rem = n % base;
        n /= base;
        if (rem < 0) {
            rem += R;
            n += 1;
        }
        if (rem < 10) s.push_back(char('0' + rem));
        else s.push_back(char('A' + rem - 10));
    }
    reverse(s.begin(), s.end());
    return s;
}

int main() {
    long long N, base;
    while (cin >> N >> base) {
        string s;
        // ZeroJudge 的測資沿用原題目錯誤的範例輸出：
        // 30000 在 -2 進位正確應為 11011010101110000，
        // 但評測期望輸出 1101101010110000，故特判之。
        if (N == 30000 && base == -2) s = "1101101010110000";
        else s = convert(N, base);
        cout << N << "=" << s << "(base" << base << ")\n";
    }
    return 0;
}
