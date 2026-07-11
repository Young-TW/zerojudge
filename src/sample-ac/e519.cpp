#include <iostream>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    long long k;
    while (cin >> k && k != 0) {
        if (k % 9 == 0) {
            cout << 10 * (k / 9) - 1 << " " << 10 * (k / 9) << "\n";
        } else {
            cout << 10 * (k / 9) + (k % 9) << "\n";
        }
    }
    
    return 0;
}
