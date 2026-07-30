#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

bool check(long long S, const vector<long long>& cnt) {
    for (int i = 6; i >= 0; --i) {
        long long unit = 1LL << i;
        long long cells = S / unit;
        long long capacity = cells * cells;
        long long need = 0;
        for (int j = 6; j >= i; --j) {
            long long factor = 1LL << (2 * (j - i));
            need += cnt[j] * factor;
        }
        if (need > capacity) return false;
    }
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    
    while (true) {
        vector<long long> cnt(7);
        cin >> cnt[0];
        if (cnt[0] == -1) break;
        for (int i = 1; i < 7; ++i) {
            cin >> cnt[i];
        }
        
        long long max_item = 1;
        bool all_zero = true;
        for (int i = 0; i < 7; ++i) {
            if (cnt[i] > 0) {
                all_zero = false;
                max_item = max(max_item, 1LL << i);
            }
        }
        if (all_zero) {
            cout << 0 << "\n";
            continue;
        }
        
        long long L = max_item;
        long long R = L;
        while (!check(R, cnt)) {
            R *= 2;
        }
        long long ans = R;
        while (L <= R) {
            long long mid = L + (R - L) / 2;
            if (check(mid, cnt)) {
                ans = mid;
                R = mid - 1;
            } else {
                L = mid + 1;
            }
        }
        cout << ans << "\n";
    }
    return 0;
}
