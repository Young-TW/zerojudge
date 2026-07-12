#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <functional>
#include <numeric>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int T;
    while (cin >> T) {
        while (T--) {
            int N;
            cin >> N;
            int P;
            cin >> P;
            vector<bool> loss(N + 1, false);
            for (int i = 0; i < P; ++i) {
                int h;
                cin >> h;
                for (int d = h; d <= N; d += h) {
                    if (d % 7 != 6 && d % 7 != 0) {
                        loss[d] = true;
                    }
                }
            }
            int count = 0;
            for (int i = 1; i <= N; ++i) {
                if (loss[i]) {
                    count++;
                }
            }
            cout << count << "\n";
        }
    }
    
    return 0;
}
