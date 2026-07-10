#include <iostream>
#include <vector>
using namespace std;

typedef long long ll;

ll mergeCount(vector<int>& a, int l, int r) {
    if (l >= r) return 0;
    int m = (l + r) / 2;
    ll cnt = mergeCount(a, l, m) + mergeCount(a, m + 1, r);
    vector<int> tmp(r - l + 1);
    int i = l, j = m + 1, k = 0;
    while (i <= m && j <= r) {
        if (a[i] <= a[j]) {
            tmp[k++] = a[i++];
        } else {
            tmp[k++] = a[j++];
            cnt += (m - i + 1);
        }
    }
    while (i <= m) tmp[k++] = a[i++];
    while (j <= r) tmp[k++] = a[j++];
    for (int t = 0; t < k; t++) a[l + t] = tmp[t];
    return cnt;
}

int main() {
    int n;
    while (cin >> n) {
        vector<int> a(n);
        for (int i = 0; i < n; i++) cin >> a[i];
        ll ans = mergeCount(a, 0, n - 1);
        cout << "Minimum exchange operations : " << ans << "\n";
    }
    return 0;
}
