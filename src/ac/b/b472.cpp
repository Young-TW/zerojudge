#include <iostream>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int win[5][5] = {};
    win[0][2] = win[0][3] = 1;
    win[1][0] = win[1][3] = 1;
    win[2][1] = win[2][4] = 1;
    win[3][2] = win[3][4] = 1;
    win[4][0] = win[4][1] = 1;
    
    int N, NA, NB;
    bool first = true;
    while (cin >> N >> NA >> NB) {
        int A[1005], B[1005];
        for (int i = 0; i < NA; i++) cin >> A[i];
        for (int i = 0; i < NB; i++) cin >> B[i];
        
        int scoreA = 0, scoreB = 0;
        for (int i = 0; i < N; i++) {
            int a = A[i % NA];
            int b = B[i % NB];
            if (a == b) continue;
            if (win[a][b]) scoreA++;
            else scoreB++;
        }
        
        if (!first) cout << "\n";
        first = false;
        cout << scoreA << " " << scoreB << "\n";
    }
    return 0;
}
