#include <iostream>
#include <vector>
#include <string>

using namespace std;

void solve() {
    int N, M;
    if (!(cin >> N >> M)) return;
    
    vector<string> grid(N);
    for (int i = 0; i < N; ++i) {
        cin >> grid[i];
    }
    
    vector<bool> R(N, false);
    vector<bool> C(M, false);
    
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            if (grid[i][j] == '#') {
                R[i] = true;
                C[j] = true;
            }
        }
    }
    
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            if (R[i] || C[j]) {
                grid[i][j] = '#';
            } else {
                grid[i][j] = 'X';
            }
        }
    }
    
    for (int i = 0; i < N; ++i) {
        cout << grid[i] << '\n';
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    while (cin) {
        solve();
    }
    return 0;
}
