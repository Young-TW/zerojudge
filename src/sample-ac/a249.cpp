#include <iostream>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int T;
    while (cin >> T) {
        while (T--) {
            int D, I;
            cin >> D >> I;
            int k = 1;
            for (int i = 1; i < D; ++i) {
                if (I & 1) {
                    k <<= 1;
                    I = (I + 1) / 2;
                } else {
                    k = (k << 1) + 1;
                    I >>= 1;
                }
            }
            cout << k << "\n";
        }
    }
    return 0;
}
