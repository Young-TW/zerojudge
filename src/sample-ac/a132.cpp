#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

int main() {
    int I;
    while (cin >> I && I != 0) {
        string b;
        int p = 0;
        int n = I;
        while (n > 0) {
            b += char('0' + (n & 1));
            p += (n & 1);
            n >>= 1;
        }
        reverse(b.begin(), b.end());
        cout << "The parity of " << b << " is " << p << " (mod 2)." << endl;
    }
    return 0;
}
