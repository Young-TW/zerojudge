#include <iostream>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    while (cin >> n && n != 0) {
        if (n <= 100) {
            cout << "f91(" << n << ") = 91\n";
        } else {
            cout << "f91(" << n << ") = " << n - 10 << "\n";
        }
    }
    
    return 0;
}
