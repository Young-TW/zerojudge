#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    const int MOD = 997;

    string s;
    while (cin >> s) {
        long long total = 0;
        int n = static_cast<int>(s.size());
        int blockIdx = 1;               // 1‑based index of the current block
        for (int i = 0; i < n; i += 3, ++blockIdx) {
            int len = min(3, n - i);
            string sub = s.substr(i, len);
            if (blockIdx % 2 == 0)       // even‑indexed block -> reverse
                reverse(sub.begin(), sub.end());
            int value = stoi(sub);       // leading zeros are ignored automatically
            total += value;
        }
        cout << (total % MOD) << '\n';
    }
    return 0;
}
