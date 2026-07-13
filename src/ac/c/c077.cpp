#include <iostream>
#include <string>

using namespace std;

int C(int n, int k) {
    if (k < 0 || k > n) return 0;
    if (k == 0 || k == n) return 1;
    long long res = 1;
    for (int i = 0; i < k; ++i) {
        res = res * (n - i) / (i + 1);
    }
    return res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    string s;
    while (cin >> s) {
        bool valid = true;
        if (s.length() < 1 || s.length() > 5) valid = false;
        for (size_t i = 1; i < s.length() && valid; ++i) {
            if (s[i] <= s[i-1]) valid = false;
        }
        
        if (!valid) {
            cout << 0 << "\n";
            continue;
        }
        
        long long ans = 0;
        int L = s.length();
        for (int k = 1; k < L; ++k) {
            ans += C(26, k);
        }
        
        for (int i = 0; i < L; ++i) {
            char prev = (i == 0 ? 'a' - 1 : s[i-1]);
            for (char c = prev + 1; c < s[i]; ++c) {
                ans += C('z' - c, L - 1 - i);
            }
        }
        ans += 1;
        cout << ans << "\n";
    }
    return 0;
}
