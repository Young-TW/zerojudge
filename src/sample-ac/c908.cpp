#include <iostream>
#include <cmath>
#include <iomanip>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int N;
    if (!(cin >> N)) return 0;
    
    cout << fixed << setprecision(3);
    
    while (N--) {
        double x1, y1, r1, x2, y2, r2;
        cin >> x1 >> y1 >> r1 >> x2 >> y2 >> r2;
        
        double dx = x2 - x1;
        double dy = y2 - y1;
        double d_sq = dx * dx + dy * dy;
        double d = sqrt(d_sq);
        
        if (d < 1e-9) {
            cout << "No Intersect\n";
            continue;
        }
        
        bool no_intersect = false;
        bool one_intersect = false;
        
        if (d > r1 + r2 + 1e-9 || d < fabs(r1 - r2) - 1e-9) {
            no_intersect = true;
        } else if (fabs(d - (r1 + r2)) < 1e-9 || fabs(d - fabs(r1 - r2)) < 1e-9) {
            one_intersect = true;
        }
        
        if (no_intersect) {
            cout << "No Intersect\n";
            continue;
        }
        
        double A = 2.0 * dx;
        double B = 2.0 * dy;
        double C = r1 * r1 - r2 * r2 - x1 * x1 + x2 * x2 - y1 * y1 + y2 * y2;
        
        if (fabs(B) > 1e-9) {
            double F = C - B * y1;
            double a = A * A + B * B;
            double b = -2.0 * (B * B * x1 + A * F);
            double c = B * B * x1 * x1 + F * F - r1 * r1 * B * B;
            
            double delta = b * b - 4.0 * a * c;
            if (delta < 0) delta = 0;
            double sqrt_delta = sqrt(delta);
            
            double x_1 = (-b - sqrt_delta) / (2.0 * a);
            double x_2 = (-b + sqrt_delta) / (2.0 * a);
            double y_1 = (C - A * x_1) / B;
            double y_2 = (C - A * x_2) / B;
            
            if (x_1 > x_2 + 1e-9 || (fabs(x_1 - x_2) <= 1e-9 && y_1 > y_2)) {
                swap(x_1, x_2);
                swap(y_1, y_2);
            }
            
            if (one_intersect || sqrt_delta < 1e-9) {
                cout << x_1 << " " << y_1 << "\n";
            } else {
                cout << x_1 << " " << y_1 << " " << x_2 << " " << y_2 << "\n";
            }
        } else {
            double x = C / A;
            double delta = r1 * r1 - (x - x1) * (x - x1);
            if (delta < 0) delta = 0;
            double sqrt_delta = sqrt(delta);
            
            double y_1 = y1 - sqrt_delta;
            double y_2 = y1 + sqrt_delta;
            
            if (one_intersect || sqrt_delta < 1e-9) {
                cout << x << " " << y_1 << "\n";
            } else {
                cout << x << " " << y_1 << " " << x << " " << y_2 << "\n";
            }
        }
    }
    
    return 0;
}
