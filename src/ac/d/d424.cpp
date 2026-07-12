#include <iostream>
#include <cstring>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int h[10005];
    memset(h, 0, sizeof(h));
    
    int L, H, R;
    while (cin >> L >> H >> R) {
        for (int i = L; i < R; ++i) {
            if (H > h[i]) {
                h[i] = H;
            }
        }
    }
    
    bool first = true;
    int prev = 0;
    for (int i = 0; i <= 10001; ++i) {
        if (h[i] != prev) {
            if (!first) cout << " ";
            cout << i << " " << h[i];
            prev = h[i];
            first = false;
        }
    }
    cout << "\n";
    
    return 0;
}
