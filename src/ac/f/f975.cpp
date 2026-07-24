#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

int main() {
    int n, k;
    while (cin >> n >> k) {
        double pi = acos(-1.0);
        double angle_n = pi / n;
        double angle_k = pi * k / n;
        
        double sin_n = sin(angle_n);
        double sin_k = sin(angle_k);
        
        double R = 1.0 / (2.0 * sin_n);
        double vr = sin_k;
        
        double time = R / vr;
        
        cout << fixed << setprecision(2) << time << endl;
    }
    return 0;
}
