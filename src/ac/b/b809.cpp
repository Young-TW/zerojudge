#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int y;
    while (cin >> y) {
        // 1. collect all digits of 1 .. y
        vector<int> dig;
        dig.reserve(7000);
        for (int i = 1; i <= y; ++i) {
            string s = to_string(i);
            for (char c : s) dig.push_back(c - '0');
        }
        int n = (int)dig.size();               // k

        // 2. binomial coefficients C(n-1, i) modulo 9
        vector<int> coeff(n, 0);
        coeff[0] = 1;                          // C(0,0)
        for (int row = 1; row < n; ++row) {
            for (int i = row; i > 0; --i) {
                int v = coeff[i] + coeff[i - 1];
                if (v >= 9) v -= 9;
                coeff[i] = v;
            }
        }

        // 3. Σ coeff[i] * dig[i] (mod 9)
        int sumMod = 0;
        for (int i = 0; i < n; ++i) {
            sumMod += coeff[i] * dig[i];
            sumMod %= 9;
        }

        // 4. output the final digit
        int ans = (sumMod == 0) ? 9 : sumMod;
        cout << ans << '\n';
    }
    return 0;
}
