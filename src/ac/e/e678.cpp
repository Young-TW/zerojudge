#include <iostream>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    long long D[13] = {0};
    long long fact[13] = {0};
    
    D[1] = 0;
    D[2] = 1;
    fact[1] = 1;
    fact[2] = 2;
    
    for (int i = 3; i <= 12; ++i) {
        D[i] = (i - 1) * (D[i - 1] + D[i - 2]);
        fact[i] = fact[i - 1] * i;
    }
    
    int t;
    while (cin >> t) {
        while (t--) {
            int n;
            cin >> n;
            cout << D[n] << "/" << fact[n] << "\n";
        }
    }
    
    return 0;
}
