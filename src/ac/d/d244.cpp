#include <iostream>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int x;
    int ones = 0, twos = 0;
    while (cin >> x) {
        ones = (ones ^ x) & ~twos;
        twos = (twos ^ x) & ~ones;
    }

    cout << twos << "\n";

    return 0;
}
