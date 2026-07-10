#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    string s;
    while (cin >> s && s != ".") {
        int n = (int)s.size();
        vector<int> f(n, 0);
        for (int i = 1; i < n; i++) {
            int j = f[i - 1];
            while (j > 0 && s[i] != s[j]) j = f[j - 1];
            if (s[i] == s[j]) j++;
            f[i] = j;
        }
        int len = n - f[n - 1];
        int ans = (n % len == 0) ? n / len : 1;
        cout << ans << "\n";
    }
    return 0;
}
