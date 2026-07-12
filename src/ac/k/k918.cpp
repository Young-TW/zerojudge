#include <iostream>
using namespace std;

int main() {
    long long t, x, y;
    while (cin >> t >> x >> y) {
        cout << (t - 1) * (x - y) + x << "\n";
    }
    return 0;
}
