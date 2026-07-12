#include <iostream>
#include <algorithm>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    while (cin >> n) {
        int overall_max = -1;
        for (int i = 0; i < n; ++i) {
            int k;
            cin >> k;
            int chain_min = 1000000;
            for (int j = 0; j < k; ++j) {
                int strength;
                cin >> strength;
                if (strength < chain_min) {
                    chain_min = strength;
                }
            }
            if (chain_min > overall_max) {
                overall_max = chain_min;
            }
        }
        cout << overall_max << "\n";
    }
    
    return 0;
}
