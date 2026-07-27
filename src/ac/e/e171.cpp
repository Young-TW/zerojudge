#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    while (cin >> n) {
        if (n == 0) break;
        vector<char> a(n);
        for (int i = 0; i < n; ++i) {
            int p; cin >> p;
            a[i] = (p != 0);          // 1 = has ticket, 0 = no ticket
        }
        int k; cin >> k;

        int left = 0, zeroCnt = 0, best = 0;
        for (int right = 0; right < n; ++right) {
            if (a[right] == 0) ++zeroCnt;
            while (zeroCnt > k) {
                if (a[left] == 0) --zeroCnt;
                ++left;
            }
            int curLen = right - left + 1;
            if (curLen > best) best = curLen;
        }
        cout << best << '\n';
    }
    return 0;
}
