#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    long long n;
    bool first = true;
    while (cin >> n) {
        long long best = LLONG_MAX;
        for (int i = 0; i < 3; i++) {
            long long cnt, price;
            cin >> cnt >> price;
            long long need = (n + cnt - 1) / cnt;
            long long cost = need * price;
            best = min(best, cost);
        }
        if (!first) cout << "\n";
        cout << best << "\n";
        first = false;
    }
    return 0;
}
