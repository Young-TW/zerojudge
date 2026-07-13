#include <iostream>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    long long a, b, c, d;
    while (cin >> a >> b >> c >> d) {
        if (a % d != 0 || b % d != 0 || c % d != 0) {
            cout << 0 << "\n";
        } else {
            cout << (a / d) * (b / d) * (c / d) << "\n";
        }
    }
    return 0;
}
