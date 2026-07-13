#include <iostream>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    long long A, B;
    while (cin >> A >> B) {
        if (A > B) {
            cout << A << "\n";
        } else {
            cout << B + 1 << "\n";
        }
    }
    
    return 0;
}
