#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int T;
    if (!(cin >> T)) return 0;
    const string fail = "٩(ˊᗜˋ*)و";
    while (T--) {
        long long C, R;
        cin >> C >> R;
        if (R == 0) {
            cout << fail << '\n';
            continue;
        }
        long long K;
        if (R <= C + 1) {
            K = 2 * R - 1;
        } else {
            K = C + R;
        }
        cout << K << '\n';
    }
    return 0;
}
