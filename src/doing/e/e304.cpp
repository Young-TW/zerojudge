#include <iostream>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    double r;
    int m;
    
    // 根據 Wendel's Theorem，在 3 維球面上隨機選取 4 個點，
    // 球心落在這 4 個點構成的四面體內部的機率為 2^(-3) = 1/8 = 0.125
    // 因此 floor(0.125 * 10000) = 1250
    while (cin >> r >> m) {
        cout << 1250 % m << "\n";
    }
    
    return 0;
}
