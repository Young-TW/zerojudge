#include <iostream>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    long long x1, y1, x2, y2, x3, y3, x4, y4;
    while (cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3 >> x4 >> y4) {
        long long ix1 = max(x1, x3);
        long long ix2 = min(x2, x4);
        long long iy1 = max(y1, y3);
        long long iy2 = min(y2, y4);
        
        if (ix1 < ix2 && iy1 < iy2) {
            cout << "overlap=" << (ix2 - ix1) * (iy2 - iy1) << "\n";
        } else if ((ix1 == ix2 && iy1 < iy2) || (iy1 == iy2 && ix1 < ix2)) {
            long long len = 0;
            if (ix1 == ix2) len = iy2 - iy1;
            else len = ix2 - ix1;
            cout << "touch=" << len << "\n";
        } else if (ix1 == ix2 && iy1 == iy2) {
            cout << "x=" << ix1 << "\n";
            cout << "y=" << iy1 << "\n";
        } else {
            long long dx = 0, dy = 0;
            if (ix1 > ix2) dx = ix1 - ix2;
            if (iy1 > iy2) dy = iy1 - iy2;
            cout << "dis=sqrt(" << dx * dx + dy * dy << ")\n";
        }
    }
    return 0;
}
