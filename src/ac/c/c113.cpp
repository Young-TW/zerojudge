#include <iostream>
#include <cstdio>
#include <cmath>
using namespace std;

int main() {
    int N;
    cin >> N;
    cout << "INTERSECTING LINES OUTPUT" << endl;
    while (N--) {
        long long x1, y1, x2, y2, x3, y3, x4, y4;
        cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3 >> x4 >> y4;
        long long dx1 = x2 - x1, dy1 = y2 - y1;
        long long dx2 = x4 - x3, dy2 = y4 - y3;
        long long cross = dx1 * dy2 - dy1 * dx2;
        if (cross == 0) {
            long long c = (x3 - x1) * dy1 - (y3 - y1) * dx1;
            if (c == 0) {
                cout << "LINE" << endl;
            } else {
                cout << "NONE" << endl;
            }
        } else {
            double t = (double)((x3 - x1) * dy2 - (y3 - y1) * dx2) / (double)cross;
            double px = (double)x1 + t * (double)dx1;
            double py = (double)y1 + t * (double)dy1;
            if (fabs(px) < 1e-9) px = 0.0;
            if (fabs(py) < 1e-9) py = 0.0;
            printf("POINT %.2f %.2f\n", px, py);
        }
    }
    cout << "END OF OUTPUT" << endl;
    return 0;
}
