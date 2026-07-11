#include <iostream>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    while (cin >> n) {
        cout << (n ^ 1) << '\n';
    }
    
    return 0;
}
