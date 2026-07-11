#include <iostream>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    long long a, b, c;
    while (cin >> a >> b >> c) {
        cout << a + b + c << "\n";
    }
    
    return 0;
}
