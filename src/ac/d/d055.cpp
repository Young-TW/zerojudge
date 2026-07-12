#include <iostream>
#include <cmath>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int N;
    while (cin >> N) {
        for (int i = 0; i < N; ++i) {
            double Ax, Ay, Bx, By, Cx, Cy;
            cin >> Ax >> Ay >> Bx >> By >> Cx >> Cy;
            
            double area_abc = 0.5 * fabs((Bx - Ax) * (Cy - Ay) - (By - Ay) * (Cx - Ax));
            double area_pqr = area_abc / 7.0;
            
            long long ans = llround(area_pqr);
            cout << ans << "\n";
        }
    }
    
    return 0;
}
