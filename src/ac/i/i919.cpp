#include <iostream>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int T;
    while (cin >> T) {
        for (int i = 1; i <= T; ++i) {
            int L, W, H;
            cin >> L >> W >> H;
            if (L <= 20 && W <= 20 && H <= 20) {
                cout << "Case " << i << ": good\n";
            } else {
                cout << "Case " << i << ": bad\n";
            }
        }
    }
    
    return 0;
}
