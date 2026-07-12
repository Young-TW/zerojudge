#include <iostream>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int R, C;
    long long K;
    while (cin >> R >> C >> K) {
        int row_start = (int)(((K - 1) % R + R) % R);
        int col_start = (int)(((K - 1) % C + C) % C);
        
        for (int i = 0; i < R; ++i) {
            int r = (row_start + i) % R;
            for (int j = 0; j < C; ++j) {
                int c = (col_start + j) % C;
                if (j > 0) cout << ' ';
                cout << 1LL * r * C + c + 1;
            }
            cout << '\n';
        }
    }
    
    return 0;
}
