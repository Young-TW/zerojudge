#include <iostream>
#include <algorithm>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int a, b, c;
    while (cin >> a >> b >> c) {
        cout << max({a, b, c}) << "\n";
    }
    
    return 0;
}
