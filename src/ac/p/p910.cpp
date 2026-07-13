#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int N, M;
    while (cin >> N >> M) {
        vector<string> grid(N * M);
        for (int i = 0; i < N * M; ++i) {
            cin >> grid[i];
        }
        string target;
        if (!(cin >> target)) break;
        
        bool found = false;
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < M; ++j) {
                if (grid[i * M + j] == target) {
                    cout << i + 1 << " " << j + 1 << "\n";
                    found = true;
                }
            }
        }
        if (!found) {
            cout << "0 0\n";
        }
    }
    
    return 0;
}
