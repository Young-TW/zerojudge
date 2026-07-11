#include <iostream>
#include <cmath>
#include <cstdio>
#include <algorithm>

using namespace std;

int main() {
    double a, b, c;
    while (cin >> a >> b >> c) {
        double d2 = a * a + c * c - b * b;
        if (d2 < 0) d2 = 0;
        double d = sqrt(d2);
        printf("%.2f\n", d);
    }
    return 0;
}
