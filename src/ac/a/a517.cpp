#include <iostream>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    unsigned long long x, y, z;
    while (cin >> x >> y >> z) {
        unsigned long long m = x;
        if (y < m) m = y;
        if (z < m) m = z;

        unsigned long long d = x + y + z - 2 * m;
        cout << d << "\n";
    }
    return 0;
}
