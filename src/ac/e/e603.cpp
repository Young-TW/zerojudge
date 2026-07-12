#include <iostream>
#include <vector>

using namespace std;

long long my_abs(long long x) {
    return x < 0 ? -x : x;
}

void extgcd(long long a, long long b, long long &x, long long &y, long long &d) {
    if (b == 0) {
        x = 1;
        y = 0;
        d = a;
    } else {
        long long x1, y1;
        extgcd(b, a % b, x1, y1, d);
        x = y1;
        y = x1 - (a / b) * y1;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    long long a, b;
    while (cin >> a >> b) {
        long long x, y, d;
        extgcd(a, b, x, y, d);
        long long stepX = b / d;
        long long stepY = a / d;
        
        vector<long long> ks;
        for (int i = -2; i <= 2; ++i) {
            ks.push_back(i);
            long long k1 = -x / stepX;
            ks.push_back(k1 + i);
            long long k2 = y / stepY;
            ks.push_back(k2 + i);
        }
        
        long long bestX = x, bestY = y;
        long long minSum = my_abs(x) + my_abs(y);
        bool bestXleY = (x <= y);
        
        for (long long k : ks) {
            long long cx = x + k * stepX;
            long long cy = y - k * stepY;
            long long sum = my_abs(cx) + my_abs(cy);
            bool cxlecy = (cx <= cy);
            
            if (sum < minSum) {
                bestX = cx;
                bestY = cy;
                minSum = sum;
                bestXleY = cxlecy;
            } else if (sum == minSum) {
                if (cxlecy && !bestXleY) {
                    bestX = cx;
                    bestY = cy;
                    bestXleY = cxlecy;
                }
            }
        }
        
        cout << bestX << " " << bestY << " " << d << "\n";
    }
    return 0;
}
