#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    long long N, M, A, B;
    while (cin >> N >> M >> A >> B) {
        long long ansX = -1, ansY = -1;
        if (A == B) {
            __int128 total = (__int128)A * M;
            if (total == (__int128)N) {
                ansX = 0;
                ansY = M;
            }
        } else {
            __int128 numerator = (__int128)N - (__int128)B * M;
            long long denom = A - B;               // may be negative
            if (denom != 0 && numerator % denom == 0) {
                __int128 x128 = numerator / denom;
                if (x128 >= 0 && x128 <= (__int128)M) {
                    ansX = (long long)x128;
                    ansY = M - ansX;
                }
            }
        }
        cout << ansX << ' ' << ansY << '\n';
    }
    return 0;
}
