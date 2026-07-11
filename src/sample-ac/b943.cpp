#include <iostream>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <functional>
#include <numeric>
#include <cstring>
#include <vector>
#include <string>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int K;
    while (cin >> K) {
        if (K == 0) break;
        double a, b, c, d;
        cin >> a >> b >> c >> d;
        
        double p = 0.0, q = 0.0;
        
        if (K == 1) {
            double r1 = hypot(a, b);
            double theta1 = atan2(b, a);
            double R = pow(r1, c) / exp(d * theta1);
            double Phi = d * log(r1) + c * theta1;
            p = R * cos(Phi);
            q = R * sin(Phi);
        } else if (K == 2) {
            double r1 = hypot(a, b);
            double theta1 = atan2(b, a);
            double r2 = hypot(c, d);
            double theta2 = atan2(d, c);
            
            double ln_r1 = log(r1);
            double ln_r2 = log(r2);
            
            double D = ln_r1 * ln_r1 + theta1 * theta1;
            
            p = (ln_r1 * ln_r2 + theta1 * theta2) / D;
            q = (ln_r1 * theta2 - ln_r2 * theta1) / D;
        }
        
        if (fabs(p) < 5e-7) p = 0.0;
        
        if (q < -5e-7) {
            printf("%.6f - %.6fi\n", p, -q);
        } else {
            printf("%.6f + %.6fi\n", p, fabs(q));
        }
    }
    
    return 0;
}
