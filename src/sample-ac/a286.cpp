#include <iostream>
#include <cstdlib>
using namespace std;

int sumDigits(long long x) {
    int s = 0;
    while (x > 0) { s += x % 10; x /= 10; }
    return s;
}

int special(long long y, long long m, long long d) {
    int s = sumDigits(y) + sumDigits(m) + sumDigits(d);
    while (s >= 10) s = sumDigits(s);
    return s;
}

int main() {
    long long y, m, d;
    while (cin >> y >> m >> d) {
        int bs = special(y, m, d);
        int n;
        cin >> n;
        int bestIdx = -1, bestDiff = -1;
        for (int i = 1; i <= n; i++) {
            long long yy, mm, dd;
            cin >> yy >> mm >> dd;
            int diff = abs(special(yy, mm, dd) - bs);
            if (bestIdx == -1 || diff < bestDiff) {
                bestDiff = diff;
                bestIdx = i;
            }
        }
        cout << bestIdx << "\n";
    }
    return 0;
}
