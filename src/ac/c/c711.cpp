#include <iostream>
#include <algorithm>
using namespace std;
using int64 = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int64 X, Y, K;
    while (cin >> X >> Y >> K) {
        if (K == 0) {
            if (X == 0 && Y == 0) cout << 0 << '\n';
            else cout << -1 << '\n';
            continue;
        }
        
        int64 A = (X >= 0) ? X : -X;
        int64 B = (Y >= 0) ? Y : -Y;
        int64 minAB = min(A, B);
        int64 maxAB = max(A, B);
        
        int pX = X & 1;
        int pY = Y & 1;
        int P = (K & 1) ^ (pX ^ pY);  // required parity of d
        
        // Interval I1: d >= maxAB
        int pen = (pX != P) + (pY != P);
        int64 upper1 = K - pen;
        if (upper1 >= maxAB) {
            int64 d = upper1;
            if ((d & 1) != P) --d;
            if (d >= maxAB) {
                cout << d << '\n';
                continue;
            }
        }
        
        // Interval I2: minAB <= d < maxAB
        if (minAB < maxAB) {
            int p_min = (A == minAB) ? pX : pY;
            if (K >= maxAB) {
                bool parity_ok = false;
                if (K >= maxAB + 1) {
                    parity_ok = true;
                } else { // K == maxAB
                    if (P == p_min) parity_ok = true;
                }
                if (parity_ok) {
                    int64 upper2 = maxAB - 1;
                    int64 d = upper2;
                    if ((d & 1) != P) --d;
                    if (d >= minAB) {
                        cout << d << '\n';
                        continue;
                    }
                }
            }
        }
        
        // Interval I3: 0 <= d < minAB
        int64 lower3 = A + B - K;
        if (lower3 < 0) lower3 = 0;
        int64 upper3 = minAB - 1;
        if (lower3 <= upper3) {
            int64 d = upper3;
            if ((d & 1) != P) --d;
            if (d >= lower3) {
                cout << d << '\n';
                continue;
            }
        }
        
        cout << -1 << '\n';
    }
    return 0;
}
