#include <iostream>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int T;
    while (cin >> T) {
        for (int t = 1; t <= T; ++t) {
            char c1, c2;
            int n;
            cin >> c1 >> c2 >> n;
            
            long long M[105][105];
            bool symmetric = true;
            
            for (int i = 0; i < n; ++i) {
                for (int j = 0; j < n; ++j) {
                    cin >> M[i][j];
                    if (M[i][j] < 0) {
                        symmetric = false;
                    }
                }
            }
            
            if (symmetric) {
                for (int i = 0; i < n && symmetric; ++i) {
                    for (int j = 0; j < n && symmetric; ++j) {
                        if (M[i][j] != M[n - 1 - i][n - 1 - j]) {
                            symmetric = false;
                        }
                    }
                }
            }
            
            cout << "Test #" << t << ": ";
            if (symmetric) {
                cout << "Symmetric.\n";
            } else {
                cout << "Non-symmetric.\n";
            }
        }
    }
    return 0;
}
