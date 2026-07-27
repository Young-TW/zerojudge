#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    const int MAXV = 100;
    long long cnt[MAXV + 1] = {0};
    int x;
    while (cin >> x) {
        if (x >= 1 && x <= MAXV) cnt[x]++;   // according to problem constraints
    }

    bool first = true;
    for (int v = 1; v <= MAXV; ++v) {
        while (cnt[v]--) {
            if (!first) cout << ' ';
            cout << v;
            first = false;
        }
    }
    cout << '\n';
    return 0;
}
