#include <iostream>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    long long dp1[20] = {0};
    long long dp2[20] = {0};
    long long dp3[20] = {0};
    
    dp1[0] = 1;
    for (int i = 1; i < 20; ++i) {
        dp1[i] = dp1[i - 1];
    }
    
    dp2[0] = 1;
    if (1 < 20) dp2[1] = 1;
    for (int i = 2; i < 20; ++i) {
        dp2[i] = dp2[i - 1] + dp2[i - 2];
    }
    
    dp3[0] = 1;
    if (1 < 20) dp3[1] = 1;
    if (2 < 20) dp3[2] = 2;
    for (int i = 3; i < 20; ++i) {
        dp3[i] = dp3[i - 1] + dp3[i - 2] + dp3[i - 3];
    }
    
    int t, k;
    while (cin >> t >> k) {
        int n = -k;
        if (t == 1) {
            cout << dp1[n] << "\n";
        } else if (t == 2) {
            cout << dp2[n] << "\n";
        } else if (t == 3) {
            cout << dp3[n] << "\n";
        }
    }
    
    return 0;
}
