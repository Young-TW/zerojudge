#include <iostream>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int N;
    if (cin >> N) {
        int ans = 0;
        for (int i = 1; i < N; ++i) {
            int x;
            cin >> x;
            ans ^= x;
        }
        cout << ans << "\n";
    }
    
    return 0;
}
