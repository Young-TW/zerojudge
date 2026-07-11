#include <iostream>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    long long a, b;
    while (cin >> a >> b) {
        long long X = 4 * a * a - b * b;
        if (X <= 0) {
            cout << 0 << "\n";
            continue;
        }
        long long k = 1;
        long long Y = X;
        while (Y % 4 == 0) {
            Y /= 4;
            k *= 2;
        }
        for (long long i = 3; i * i <= Y; i += 2) {
            while (Y % (i * i) == 0) {
                Y /= (i * i);
                k *= i;
            }
        }
        if (Y == 1) {
            cout << k << "\n";
        } else if (k == 1) {
            cout << "√" << Y << "\n";
        } else {
            cout << k << "√" << Y << "\n";
        }
    }
    return 0;
}
