#include <iostream>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int N, M;
    while (cin >> N >> M) {
        int xor_sum = 0;
        for (int i = 0; i < N; ++i) {
            int X, Y;
            cin >> X >> Y;
            int dist = Y - X - 1;
            xor_sum ^= dist % (M + 1);
        }
        if (xor_sum != 0) {
            cout << "OpenChan\n";
        } else {
            cout << "Kitty\n";
        }
    }
    
    return 0;
}
