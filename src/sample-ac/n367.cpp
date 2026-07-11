#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

bool is_triangle(long long A, long long B, long long C) {
    if (A + B < C) {
        long long diff = C - A - B;
        if (4 * A * B <= diff * diff) return false;
    }
    if (B + C < A) {
        long long diff = A - B - C;
        if (4 * B * C <= diff * diff) return false;
    }
    if (C + A < B) {
        long long diff = B - C - A;
        if (4 * C * A <= diff * diff) return false;
    }
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    long long A, B, C;
    while (cin >> A >> B >> C) {
        if (is_triangle(A, B, C)) {
            double x = (A + C - B) / 2.0;
            double y = (A + B - C) / 2.0;
            double z = (B + C - A) / 2.0;
            double area = sqrt(x * y + y * z + z * x) / 2.0;
            
            cout << fixed << setprecision(4);
            cout << x << "\n";
            cout << y << "\n";
            cout << z << "\n";
            cout << area << "\n";
        } else {
            cout << "error\n";
        }
    }
    return 0;
}
