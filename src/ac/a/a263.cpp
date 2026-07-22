#include <iostream>
#include <cmath>

using namespace std;

bool isLeap(int y) {
    if (y % 400 == 0) return true;
    if (y % 100 == 0) return false;
    if (y % 4 == 0) return true;
    return false;
}

int daysInMonth(int y, int m) {
    if (m == 1 || m == 3 || m == 5 || m == 7 || m == 8 || m == 10 || m == 12) return 31;
    if (m == 4 || m == 6 || m == 9 || m == 11) return 30;
    if (m == 2) return isLeap(y) ? 29 : 28;
    return 0;
}

long long dateToDays(int y, int m, int d) {
    long long total = 0;
    if (y > 0) {
        total += (long long)(y - 1) * 365 + (y - 1) / 4 - (y - 1) / 100 + (y - 1) / 400;
    } else {
        total -= (long long)(-y) * 365 + (-y) / 4 - (-y) / 100 + (-y) / 400;
    }
    for (int i = 1; i < m; ++i) {
        total += daysInMonth(y, i);
    }
    total += d;
    return total;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int y1, m1, d1;
    while (cin >> y1 >> m1 >> d1) {
        int y2, m2, d2;
        cin >> y2 >> m2 >> d2;
        long long days1 = dateToDays(y1, m1, d1);
        long long days2 = dateToDays(y2, m2, d2);
        cout << abs(days1 - days2) << "\n";
    }
    return 0;
}
