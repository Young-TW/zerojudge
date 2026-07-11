#include <iostream>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    long long H, W;
    while (cin >> H >> W) {
        cout << 2 * (H + W) << "\n";
    }
    
    return 0;
}
