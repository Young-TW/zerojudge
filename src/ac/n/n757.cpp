#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int T;
    while (cin >> T) {
        while (T--) {
            int L;
            cin >> L;
            double pi = acos(-1.0);
            double R = L / 5.0;
            double W = L * 6.0 / 10.0;
            double red = pi * R * R;
            double green = L * W - red;
            cout << fixed << setprecision(2) << red << " " << green << "\n";
        }
    }
    
    return 0;
}
