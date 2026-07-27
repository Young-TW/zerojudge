#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    long long N;
    while (cin >> N) {
        long long R = 0, G = 0, B = 0;
        for (long long i = 1; i <= N; ++i) {
            long long sz = 1LL << (i - 1);          // size of the i‑th layer
            long long base = sz / 3;
            long long rem  = sz % 3;
            R += base; G += base; B += base;
            if (rem >= 1) ++R;
            if (rem == 2) ++G;
        }
        cout << R << ' ' << G << ' ' << B << '\n';
    }
    return 0;
}
