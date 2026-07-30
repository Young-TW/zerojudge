#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int N;
    while (cin >> N) {
        while (N--) {
            int D, L;
            cin >> D >> L;
            double area = acos(-1.0) * L * sqrt((double)L * L - (double)D * D) / 4.0;
            cout << fixed << setprecision(3) << area << "\n";
        }
    }
    
    return 0;
}
