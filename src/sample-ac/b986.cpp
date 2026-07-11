#include <iostream>

using namespace std;

void exgcd(long long a, long long b, long long &x, long long &y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return;
    }
    long long x1, y1;
    exgcd(b, a % b, x1, y1);
    x = y1;
    y = x1 - (a / b) * y1;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    long long a, b;
    while (cin >> a >> b) {
        long long x, y;
        exgcd(a, b, x, y);
        x = (x % b + b) % b;
        if (x == 0) x = b;
        cout << x << "\n";
    }
    return 0;
}
