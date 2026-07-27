#include <bits/stdc++.h>
using namespace std;
using int64 = long long;

/* position of value v (1 .. n^2) inside an odd order magic square n */
static pair<int64,int64> oddPos(int64 n, int64 v) {
    int64 t = v - 1;                 // steps already taken
    int64 a = t / n;                 // how many "down" moves
    int64 row = (-t + 2 * a) % n;
    if (row < 0) row += n;
    int64 col = (n / 2 + t - a) % n;
    if (col < 0) col += n;
    return {row, col};               // 0‑based
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int64 N, K;
    while (cin >> N >> K) {
        if (N % 2 == 1) {                     // odd order
            auto p = oddPos(N, K);
            cout << p.first + 1 << ' ' << p.second + 1 << '\n';
        }
        else if (N % 4 == 0) {                // doubly even
            int64 r = (K - 1) / N;
            int64 c = (K - 1) % N;
            bool inv = ( (r % 4 == c % 4) || ((r % 4) + (c % 4) == 3) );
            if (inv) {
                int64 orig = N * N + 1 - K;
                r = (orig - 1) / N;
                c = (orig - 1) % N;
            }
            cout << r + 1 << ' ' << c + 1 << '\n';
        }
        else {                                 // singly even
            int64 M = N / 2;                    // odd
            int64 k = (N - 2) / 4;              // 1 ≤ k ≤ M/2
            int64 block = (K - 1) / (M * M);    // 0:A 1:D 2:B 3:C
            int64 innerVal = (K - 1) % (M * M) + 1;
            auto p = oddPos(M, innerVal);
            int64 i0 = p.first, j0 = p.second;

            int64 r, c;
            if (block == 0) { r = i0;          c = j0; }          // A
            else if (block == 1) { r = M + i0; c = M + j0; }    // D
            else if (block == 2) { r = i0;    c = M + j0; }    // B
            else {               r = M + i0; c = j0; }          // C

            if (block == 0 || block == 3) {   // possible A↔C swap
                bool needSwap = false;
                if (c < k) needSwap = true;                                   // left part
                else if (c >= N - (k - 1)) needSwap = true;                    // right part
                else if (i0 == M / 2 && c == k) needSwap = true;              // middle row special column
                if (needSwap) {
                    if (block == 0) r = M + i0;   // move to C
                    else            r = i0;       // move to A
                }
            }
            cout << r + 1 << ' ' << c + 1 << '\n';
        }
    }
    return 0;
}
