#include <iostream>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    long long n, k;
    while (cin >> n >> k) {
        if (n == 0) {
            cout << "Ok!\n";
        } else if (k == 0) {
            cout << "Impossib1e!\n";
        } else {
            cout << (n % k == 0 ? "Ok!" : "Impossib1e!") << "\n";
        }
    }
    return 0;
}
