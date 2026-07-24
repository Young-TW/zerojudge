#include <iostream>
#include <cstdio>
#include <cmath>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    long long T, H, W;
    const double factor = sqrt(2.0) / 2.0;   // projection factor for 45°
    while (cin >> T >> H >> W) {
        // periods
        long long perX = 2LL * W;
        long long perY = 2LL * H;
        
        long long rx = T % perX;
        long long ry = T % perY;
        
        long long x = (rx <= W) ? rx : perX - rx;
        long long y = (ry <= H) ? ry : perY - ry;
        
        double xf = x * factor;
        double yf = y * factor;
        
        // small epsilon to avoid cases like 0.0499999 being printed as 0.0
        printf("x=%.1f y=%.1f\n", xf + 1e-9, yf + 1e-9);
    }
    return 0;
}
