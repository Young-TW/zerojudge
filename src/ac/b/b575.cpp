#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int N, K;
    while (cin >> N >> K) {
        vector<string> cur(N);
        for (int i = 0; i < N; ++i) {
            cin >> cur[i];
        }
        
        vector<vector<string>> rotations(4, vector<string>(N, string(N, ' ')));
        rotations[0] = cur;
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                rotations[1][i][j] = cur[N - 1 - j][i];
                rotations[2][i][j] = cur[N - 1 - i][N - 1 - j];
                rotations[3][i][j] = cur[j][N - 1 - i];
            }
        }
        
        int ans = 0;
        for (int k = 0; k < K; ++k) {
            vector<string> mem(N);
            for (int i = 0; i < N; ++i) {
                cin >> mem[i];
            }
            for (int r = 0; r < 4; ++r) {
                if (mem == rotations[r]) {
                    ans++;
                    break;
                }
            }
        }
        cout << ans << "\n";
    }
    
    return 0;
}
