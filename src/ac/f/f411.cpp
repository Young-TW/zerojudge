#include <bits/stdc++.h>
using namespace std;

long long minSwapsToPalindrome(vector<long long> a) {
    int n = (int)a.size();
    long long swaps = 0;
    int i = 0, j = n - 1;
    while (i < j) {
        if (a[i] == a[j]) {
            ++i;
            --j;
            continue;
        }
        int k = j;
        while (k > i && a[k] != a[i]) --k;

        if (k == i) {                     // no partner, must become centre
            swap(a[i], a[i + 1]);
            ++swaps;
        } else {                          // bring partner from k to j
            for (int l = k; l < j; ++l) {
                swap(a[l], a[l + 1]);
            }
            swaps += (j - k);
            ++i;
            --j;
        }
    }
    return swaps;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    while (cin >> n) {
        vector<long long> a(n);
        unordered_map<long long, int> freq;
        for (int i = 0; i < n; ++i) {
            cin >> a[i];
            ++freq[a[i]];
        }

        int odd = 0;
        for (auto &p : freq) if (p.second & 1) ++odd;
        if ((n & 1) == 0) {
            if (odd != 0) {
                cout << "Impossible\n";
                continue;
            }
        } else {
            if (odd != 1) {
                cout << "Impossible\n";
                continue;
            }
        }

        long long ans = minSwapsToPalindrome(a);
        cout << ans << '\n';
    }
    return 0;
}
