#include <iostream>
#include <cmath>
#include <algorithm>
#include <iomanip>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int N;
    while (cin >> N) {
        cout << fixed << setprecision(5);
        for (int i = 0; i < N; ++i) {
            double cx, cy, R;
            double x1, y1, x2, y2;
            cin >> cx >> cy >> R >> x1 >> y1 >> x2 >> y2;
            
            double dx = x2 - x1;
            double dy = y2 - y1;
            double fx = x1 - cx;
            double fy = y1 - cy;
            
            double A = dx * dx + dy * dy;
            if (A == 0) {
                cout << "No Intersect\n";
                continue;
            }
            double B = 2 * (fx * dx + fy * dy);
            double C = fx * fx + fy * fy - R * R;
            
            double discriminant = B * B - 4 * A * C;
            double eps = 1e-9;
            
            if (discriminant < -eps) {
                cout << "No Intersect\n";
            } else {
                double sqrtD = (discriminant > 0) ? sqrt(discriminant) : 0.0;
                double t1 = (-B - sqrtD) / (2 * A);
                double t2 = (-B + sqrtD) / (2 * A);
                
                double px1 = x1 + t1 * dx;
                double py1 = y1 + t1 * dy;
                double px2 = x1 + t2 * dx;
                double py2 = y1 + t2 * dy;
                
                if (px1 > px2 || (px1 == px2 && py1 > py2)) {
                    swap(px1, px2);
                    swap(py1, py2);
                }
                
                cout << px1 << " " << py1 << " " << px2 << " " << py2 << "\n";
            }
        }
    }
    return 0;
}
