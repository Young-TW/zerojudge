#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    double T, n;
    while (cin >> T >> n) {
        double t = -T * log2(n);
        cout << fixed << setprecision(3) << t << "\n";
    }
    
    return 0;
}
