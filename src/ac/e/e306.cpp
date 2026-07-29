// ZeroJudge e306 - Xor 運算 Again!
// 給二進位 L (可達 2^923000)。求非負整數有序對 (a,b) 使 a+b<=L 且 a+b = a XOR b 的對數 mod 1e9+7。
// a+b = a^b  <=>  a&b = 0 (無進位)。給定 s=a+b(=a|b), 拆法數 = 2^popcount(s)。
// 故答案 = sum_{s=0}^{L} 2^popcount(s)。
// 對 L 做位元 DP: 由 MSB 往下, 維護與 L 前綴相同時已固定的 1 個數 prefPop (係數 2^prefPop)。
//   遇到 L 的某位為 1: 把該位設 0, 其後 i 個低位自由 -> 貢獻 2^prefPop * 3^i; 再保持該位=1 (prefPop++)。
//   全部走完後加上 s=L 本身: 2^prefPop。
// (sum over 2^j 個 s 的 2^popcount = 3^j, 因每位貢獻因子 (1+2)。)
#include <bits/stdc++.h>
using namespace std;
const long long MOD = 1000000007LL;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    vector<string> lines;
    string s;
    size_t maxlen = 1;
    while (getline(cin, s)) {
        // 去除 \r 及前後空白
        string t;
        for (char c : s) if (c == '0' || c == '1') t += c;
                         else if (!isspace((unsigned char)c)) { t.clear(); break; } // 非二進位字元 -> 略過該行
        if (t.empty()) continue;
        // 去前導零(題目保證無, 但穩健起見保留至少一位)
        size_t p = 0; while (p + 1 < t.size() && t[p] == '0') p++;
        t = t.substr(p);
        lines.push_back(t);
        maxlen = max(maxlen, t.size());
    }
    // 預先算 3 的次方
    vector<long long> pow3(maxlen + 1);
    pow3[0] = 1;
    for (size_t i = 1; i <= maxlen; i++) pow3[i] = pow3[i-1] * 3 % MOD;

    for (auto &L : lines) {
        int len = (int)L.size();
        long long res = 0, cur2 = 1; // cur2 = 2^prefPop
        for (int j = 0; j < len; j++) {
            if (L[j] == '1') {
                int lower = len - 1 - j;       // 該位以下的自由位數
                res = (res + cur2 * pow3[lower]) % MOD;
                cur2 = cur2 * 2 % MOD;
            }
        }
        res = (res + cur2) % MOD;              // s = L 本身
        cout << res << "\n";
    }
    return 0;
}
