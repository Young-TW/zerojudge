#include <iostream>

using namespace std;

long long extgcd(long long a, long long b, long long &x, long long &y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    long long x1, y1;
    long long g = extgcd(b, a % b, x1, y1);
    x = y1;
    y = x1 - (a / b) * y1;
    return g;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    long long a, p;
    while (cin >> a >> p) {
        long long x, y;
        long long g = extgcd(a, p, x, y);
        if (g != 1) {
            cout << "No Inverse\n";
        } else {
            x = (x % p + p) % p;
            cout << x << "\n";
        }
    }
    
    return 0;
}
