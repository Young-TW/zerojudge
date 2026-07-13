#include <iostream>
#include <algorithm>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    long long M, S, T;
    bool first = true;
    while (cin >> M >> S >> T) {
        if (!first) cout << "\n";
        first = false;
        
        if (S == 0) {
            cout << "Yes\n0\n";
            continue;
        }
        
        long long bestTime = -1;
        long long maxH = 0;
        long long maxDist = 0;
        
        for (long long t = 1; t <= T; t++) {
            long long val = (M + 4 * t) / 14;
            long long g = 60LL * min(t, val);
            long long h = g - 17 * t;
            if (h > maxH) maxH = h;
            long long dist = 17 * t + maxH;
            if (dist >= S) {
                bestTime = t;
                break;
            }
            if (dist > maxDist) maxDist = dist;
        }
        
        if (bestTime != -1) {
            cout << "Yes\n" << bestTime << "\n";
        } else {
            cout << "No\n" << maxDist << "\n";
        }
    }
    return 0;
}
