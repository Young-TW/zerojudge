#include <iostream>
#include <cmath>
using namespace std;

int main() {
    int a, b;
    while (cin >> a >> b) {
        if (a == 0) {
            cout << 1 << endl;
            continue;
        }
        double log_val = b * log10(a);
        int digits = (int)floor(log_val) + 1;
        cout << digits << endl;
    }
    return 0;
}
