#include <iostream>
using namespace std;

int main() {
    int n;
    while (cin >> n) {
        int t[5];
        for (int i = 1; i <= 4; i++) cin >> t[i];
        int prev;
        cin >> prev;
        bool ok = true;
        for (int i = 1; i < 8; i++) {
            int cur;
            cin >> cur;
            int lo = min(prev, cur);
            int hi = max(prev, cur);
            int cost = 0;
            for (int f = lo; f < hi; f++) cost += t[f];
            if (cost > n) ok = false;
            prev = cur;
        }
        cout << (ok ? "yes" : "no") << "\n";
    }
    return 0;
}
