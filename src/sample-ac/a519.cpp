#include <iostream>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    unsigned long long ancestors[85];
    ancestors[1] = 1;
    ancestors[2] = 2;
    for (int i = 3; i <= 80; ++i) {
        ancestors[i] = ancestors[i - 1] + ancestors[i - 2];
    }
    
    int n;
    while (cin >> n && n != 0) {
        cout << ancestors[n] << "\n";
    }
    
    return 0;
}
