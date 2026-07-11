#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    double r;
    int n;
    double pi = acos(-1.0);
    
    while (cin >> r >> n) {
        double area = 0.5 * n * r * r * sin(2.0 * pi / n);
        cout << fixed << setprecision(3) << area << "\n";
    }
    
    return 0;
}
