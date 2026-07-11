#include <iostream>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    while (cin >> n && n != 0) {
        cout << n / 2 << "\n";
    }
    
    return 0;
}
