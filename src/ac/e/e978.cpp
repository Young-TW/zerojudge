#include <iostream>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    while (cin >> n && n) {
        if (n == 1) {
            cout << "0/1\n";
        } else {
            cout << "1/2\n";
        }
    }
    
    return 0;
}
