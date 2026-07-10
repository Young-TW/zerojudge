#include <iostream>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    unsigned n;
    while (cin >> n && n != 0) {
        // Number of carries when adding 1 in binary
        // = number of trailing 1-bits of n
        // = ctz of bitwise-complement of n.
        // n <= 2147483647 (0x7FFFFFFF), so ~n != 0; ctz is well-defined.
        cout << __builtin_ctz(~n) << "\n";
    }
    return 0;
}
