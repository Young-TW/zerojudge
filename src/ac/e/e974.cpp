#include <bits/stdc++.h>
using namespace std;

// return (decimal string s) mod m   (m > 0)
long long modString(const string &s, long long m) {
    long long r = 0;
    for (char ch : s) {
        r = (r * 10 + (ch - '0')) % m;
    }
    return r;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    long long R, C;
    string K;
    while (cin >> R >> C >> K) {
        // special case R==0 or C==0 never occurs in the problem,
        // but keep the code safe.
        if (R == 0 || C == 0) continue;

        long long mod2R = modString(K, 2 * R);
        long long mod2C = modString(K, 2 * C);

        long long rowShift = ((mod2R - 1 + 2 * R) % (2 * R)) / 2; // ((N-1)//2) % R
        long long colShift = mod2C / 2;                         // (N//2) % C

        for (long long i = 0; i < R; ++i) {
            long long origRow = (i - rowShift + R) % R;
            for (long long j = 0; j < C; ++j) {
                long long origCol = (j - colShift + C) % C;
                long long seat = origRow * C + origCol + 1;
                if (j) cout << ' ';
                cout << seat;
            }
            cout << '\n';
        }
    }
    return 0;
}
