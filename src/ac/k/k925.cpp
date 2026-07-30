#include <iostream>
#include <vector>
#include <climits>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int L;
    while (cin >> L) {
        vector<int> h(L);
        for (int i = 0; i < L; ++i) cin >> h[i];
        long long T;
        cin >> T;

        int maxH = h[0];
        int P = 1; // 1-based position of the unique highest block
        for (int i = 0; i < L; ++i) {
            if (h[i] > maxH) { maxH = h[i]; P = i + 1; }
        }

        long long up = (long long)maxH + 1 - h[0]; // rise in place at block 1 to maxH+1
        long long tP = up + (P - 1);               // time arriving above the highest block
        long long ans;

        if (T <= up) {
            ans = 1;
        } else if (T <= tP) {
            ans = 1 + (T - up);
        } else {
            long long rem = T - tP;
            int q;
            if (P == L) {
                // turn back: lowest block among 2..L (exclude initial); tie -> nearest to L (largest index)
                int mn = INT_MAX;
                q = L;
                for (int i = 1; i < L; ++i) { // 0-based i -> block i+1 (blocks 2..L)
                    if (h[i] <= mn) { mn = h[i]; q = i + 1; }
                }
                long long dist = (long long)P - q; // moving left
                ans = (rem <= dist) ? (long long)P - rem : (long long)q;
            } else {
                // continue right: highest block among P+1..L; tie -> nearest to P (smallest index)
                int mx = INT_MIN;
                q = P + 1;
                for (int i = P; i < L; ++i) { // 0-based i -> block i+1 (blocks P+1..L)
                    if (h[i] > mx) { mx = h[i]; q = i + 1; }
                }
                long long dist = (long long)q - P; // moving right
                ans = (rem <= dist) ? (long long)P + rem : (long long)q;
            }
        }
        cout << ans << '\n';
    }
    return 0;
}
