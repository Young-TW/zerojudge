#include <iostream>
#include <string>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    string p, c;
    while (cin >> p >> c) {
        int k = (c[0] - p[0] + 26) % 26;
        cout << k << '\n';
    }
    
    return 0;
}
