#include <bits/stdc++.h>
using namespace std;
using int64 = long long;

// Euclidean algorithm for non‑negative numbers
static int64 gcd_int64(int64 a, int64 b) {
    if (a < 0) a = -a;
    if (b < 0) b = -b;
    while (b) {
        int64 t = a % b;
        a = b;
        b = t;
    }
    return a;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int T;
    while (cin >> T) {               // read number of test cases (may appear multiple times)
        while (T--) {
            int N;
            if (!(cin >> N)) return 0;
            vector<int64> a(N);
            for (int i = 0; i < N; ++i) cin >> a[i];
            if (N == 0) {
                cout << 0 << '\n';
                continue;
            }
            sort(a.begin(), a.end());
            int64 g = 0;
            for (int i = 1; i < N; ++i) {
                int64 diff = a[i] - a[i - 1];
                g = gcd_int64(g, diff);
            }
            cout << g << '\n';
        }
    }
    return 0;
}
