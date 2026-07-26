#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int X;
    string N;
    while (cin >> X >> N) {
        const int MAX_SUM = 199 * 9 + 5;          // safe upper bound
        vector<int> cnt(MAX_SUM, 0);
        bool ok = false;
        int i = static_cast<int>(N.size());
        while (i > 0 && !ok) {
            int start = max(0, i - X);
            int sum = 0;
            for (int j = start; j < i; ++j) sum += N[j] - '0';
            ++cnt[sum];
            if (cnt[sum] >= 2) ok = true;
            i = start;
        }
        cout << (ok ? "Yes" : "No") << '\n';
    }
    return 0;
}
