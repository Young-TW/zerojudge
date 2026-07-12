#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    double s1, s2, s3;
    while (cin >> s1 >> s2 >> s3) {
        double t1 = sqrt(s1 * s2 / s3);
        double t2 = sqrt(s2 * s3 / s1);
        double t3 = sqrt(s3 * s1 / s2);
        double sum = t1 + t2 + t3;
        double ans = 0.5 * sum * sum;
        cout << fixed << setprecision(2) << ans << "\n";
    }
    
    return 0;
}
