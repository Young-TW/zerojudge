#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int T;
    while (cin >> T) {
        while (T--) {
            int N, S;
            cin >> N >> S;
            vector<int> x(N), y(N);
            for (int i = 0; i < N; ++i) {
                cin >> x[i] >> y[i];
            }
            int X, Y;
            cin >> X >> Y;
            
            long long S_sq = (long long)S * S;
            int visible = 0;
            for (int i = 0; i < N; ++i) {
                long long dx = x[i] - X;
                long long dy = y[i] - Y;
                if (dx * dx + dy * dy <= S_sq) {
                    visible++;
                }
            }
            cout << visible << "\n";
        }
    }
    return 0;
}
