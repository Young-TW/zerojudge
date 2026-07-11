#include <iostream>
using namespace std;

int main() {
    long long m1, m2, r;
    while (cin >> m1 >> m2 >> r) {
        __int128 result = (__int128)6 * m1 * m2 / ((__int128)r * r);
        cout << (long long)result << endl;
    }
    return 0;
}
