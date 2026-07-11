#include <iostream>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int idx[200] = {0};
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 16; ++j) {
            int p;
            if (cin >> p) {
                idx[p] += (1 << (4 - i));
            }
        }
    }
    
    int ans[32] = {0};
    for (int i = 0; i < 200; ++i) {
        if (idx[i] >= 1 && idx[i] <= 31) {
            ans[idx[i]] = i;
        }
    }
    
    for (int i = 1; i <= 31; ++i) {
        cout << ans[i];
        if (i < 31) cout << " ";
    }
    cout << "\n";
    
    return 0;
}
