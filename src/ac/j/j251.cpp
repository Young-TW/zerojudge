#include <iostream>
#include <cmath>
#include <cstdlib>
using namespace std;

int main() {
    long long x1, y1, x2, y2, x3, y3;
    while (cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3) {
        __int128 area2 = (__int128)x1 * (y2 - y3) + 
                         (__int128)x2 * (y3 - y1) + 
                         (__int128)x3 * (y1 - y2);
        if (area2 < 0) area2 = -area2;
        cout << (long long)area2 << endl;
    }
    return 0;
}
