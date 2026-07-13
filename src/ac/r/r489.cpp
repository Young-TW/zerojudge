#include <iostream>
#include <algorithm>

using namespace std;

int A[205][205];
int B[205][205];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int R, C;
    while (cin >> R >> C) {
        for (int i = 0; i < R; ++i) {
            for (int j = 0; j < C; ++j) {
                cin >> A[i][j];
            }
        }
        for (int i = 0; i < R; ++i) {
            for (int j = 0; j < C; ++j) {
                cin >> B[i][j];
            }
        }
        
        int max_sim = 0;
        int total = R * C;
        
        // 0 degrees
        int sim0 = 0;
        for (int i = 0; i < R; ++i) {
            for (int j = 0; j < C; ++j) {
                if (A[i][j] == B[i][j]) sim0++;
            }
        }
        max_sim = max(max_sim, sim0);
        
        // 180 degrees
        int sim180 = 0;
        for (int i = 0; i < R; ++i) {
            for (int j = 0; j < C; ++j) {
                if (A[i][j] == B[R - 1 - i][C - 1 - j]) sim180++;
            }
        }
        max_sim = max(max_sim, sim180);
        
        if (R == C) {
            // 90 degrees
            int sim90 = 0;
            for (int i = 0; i < R; ++i) {
                for (int j = 0; j < C; ++j) {
                    if (A[i][j] == B[C - 1 - j][i]) sim90++;
                }
            }
            max_sim = max(max_sim, sim90);
            
            // 270 degrees
            int sim270 = 0;
            for (int i = 0; i < R; ++i) {
                for (int j = 0; j < C; ++j) {
                    if (A[i][j] == B[j][R - 1 - i]) sim270++;
                }
            }
            max_sim = max(max_sim, sim270);
        }
        
        cout << (max_sim * 100 / total) << "%\n";
    }
    return 0;
}
