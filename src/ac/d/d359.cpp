#include <iostream>
#include <cstdio>

using namespace std;

int main() {
    long long S, x, y, z;
    while (cin >> S >> x >> y >> z) {
        if (S == 0 && x == 0 && y == 0 && z == 0) break;
        long long num = (x * y * z - 1) * (x * y * z - 1);
        long long den = (x * y + x + 1) * (y * z + y + 1) * (z * x + z + 1);
        double ans = (double)S * num / den;
        printf("%.2f\n", ans);
    }
    return 0;
}
