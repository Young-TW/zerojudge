#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdint>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    vector<int> inputs;
    int n;
    while (cin >> n) {
        inputs.push_back(n);
    }
    if (inputs.empty()) return 0;
    
    int max_m = 0;
    for (int x : inputs) {
        max_m = max(max_m, x / 2);
    }
    
    const int MOD = 1000000000;
    vector<int> motzkin(max_m + 1);
    motzkin[0] = 1;
    if (max_m >= 1) motzkin[1] = 1;
    
    for (int i = 2; i <= max_m; ++i) {
        __int128 sum = motzkin[i - 1];
        int limit = i - 2;
        for (int k = 0; k <= limit / 2; ++k) {
            long long term = static_cast<long long>(motzkin[k]) * motzkin[limit - k];
            if (k == limit - k) {
                sum += term;
            } else {
                sum += 2 * term;
            }
        }
        motzkin[i] = static_cast<int>(sum % MOD);
    }
    
    for (int x : inputs) {
        cout << motzkin[x / 2] << '\n';
    }
    
    return 0;
}
